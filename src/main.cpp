#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

struct WorkoutDataPoint {
	std::string name;
	double distance;
	int moving_time;
	int elapsed_time;
	double total_elevation_gain;
	std::string type;
	std::string sport_type;
	std::string workout_type;
	int id;
	std::string start_date;
	std::string start_date_local;
	std::string timezone;
	std::string location_city;
	std::string location_state;
	std::string location_country;

	//todo decide which other data points to add
	double average_speed;
	double max_speed;
	bool has_heartrate;
	double average_heartrate;
	double max_heartrate;
	double elev_high;
	double elev_low;
};


void loadEnvFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			size_t equalsPos = line.find('=');
			if (equalsPos != std::string::npos) {
				std::string key = line.substr(0, equalsPos);
				std::string value = line.substr(equalsPos + 1);
				setenv(key.c_str(), value.c_str(), 1);
			}
		}
		file.close();
	} else {
		std::cerr << "Failed to open environment file: " << filename << std::endl;
	}
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
	size_t newLength = size*nmemb;
	size_t oldLength = s->size();
	try {
		s->resize(oldLength + newLength);
	}
	catch(std::bad_alloc &e) {
		return 0;
	}

	std::copy((char*)contents, (char*)contents+newLength, s->begin()+oldLength);
	return size*nmemb;
}

nlohmann::json getJsonFromUrl(const std::string& url, const std::string& header, const std::string& postFields = "") {
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		if (!postFields.empty()) {
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
		}
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, header.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return nlohmann::json::parse(readBuffer);
}

int main() {
	loadEnvFromFile(".env");

	const char* client_id = std::getenv("CLIENT_ID");
	const char* client_secret = std::getenv("STRAVA_CLIENT_SECRET");
	const char* refresh_token = std::getenv("STRAVA_REFRESH_TOKEN");

	if (!client_id || !client_secret || !refresh_token) {
		std::cerr << "Error: Missing environment variables." << std::endl;
		return 1;
	}
	
	std::string auth_url = "https://www.strava.com/oauth/token";
	std::string activities_url = "https://www.strava.com/api/v3/athlete/activities";
	std::string postFields = "client_id=" + std::string(client_id) + "&client_secret=" + std::string(client_secret) + "&refresh_token=" + std::string(refresh_token) + "&grant_type=refresh_token&f=json";
	std::string header = "";

	std::cout << "Requesting Token...\n";
	nlohmann::json res = getJsonFromUrl(auth_url, header, postFields);
	std::string access_token = res["access_token"];
	std::cout << "Access Token = " << access_token << "\n";

	header = "Authorization: Bearer " + access_token;
	postFields = "per_page=200&page=1";
	nlohmann::json my_dataset = getJsonFromUrl(activities_url, header);


	std::cout << my_dataset[0]["name"] << "\n";
	std::cout << my_dataset[0]["map"]["summary_polyline"] << "\n";


	return 0;
}

