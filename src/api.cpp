#include "../include/api.h"
#include "../include/workoutdatapoint.h"

std::vector<WorkoutDataPoint> convertJsonToVector(const nlohmann::json &jsonArray) {
  std::vector<WorkoutDataPoint> workoutDataPoints;

  for (const auto &jsonObject : jsonArray) {
    WorkoutDataPoint workoutDataPoint;

    // need to check .isnull for string fields
    // need to check if field exists for all fields
    workoutDataPoint.name = jsonObject.contains("name") && !jsonObject["name"].is_null() ? jsonObject["name"] : "";
    workoutDataPoint.distance = jsonObject.contains("distance") ? jsonObject["distance"].get<double>() : 0.0;

    workoutDataPoint.moving_time = jsonObject.contains("moving_time") ? jsonObject["moving_time"].get<int>() : 0;
    workoutDataPoint.elapsed_time = jsonObject.contains("elapsed_time") ? jsonObject["elapsed_time"].get<int>() : 0;

    workoutDataPoint.type = jsonObject.contains("name") && !jsonObject["type"].is_null() ? jsonObject["type"] : "";
    workoutDataPoint.sport_type = jsonObject.contains("sport_type") && !jsonObject["sport_type"].is_null() ? jsonObject["sport_type"] : "";
    workoutDataPoint.workout_type = jsonObject.contains("workout_type") && !jsonObject["workout_type"].is_null() ? jsonObject["workout_type"].get<int>() : -1;

    workoutDataPoint.id = jsonObject.contains("id") ? jsonObject["id"].get<int>() : 0;

    workoutDataPoint.start_date = jsonObject.contains("start_date") && !jsonObject["start_date"].is_null() ? jsonObject["start_date"] : "";

    workoutDataPoint.start_date_local = jsonObject.contains("start_date_local") && !jsonObject["start_date_local"].is_null() ? jsonObject["start_date_local"] : "";
    workoutDataPoint.timezone = jsonObject.contains("timezone") && !jsonObject["timezone"].is_null() ? jsonObject["timezone"] : "";

    workoutDataPoint.location_city = jsonObject.contains("location_city") && !jsonObject["location_city"].is_null() ? jsonObject["location_city"] : "";
    workoutDataPoint.location_state = jsonObject.contains("location_state") && !jsonObject["location_state"].is_null() ? jsonObject["location_state"] : "";
    workoutDataPoint.location_country = jsonObject.contains("location_country") && !jsonObject["location_country"].is_null() ? jsonObject["location_country"] : "";

    workoutDataPoint.average_speed = jsonObject.contains("average_speed") ? jsonObject["average_speed"].get<double>() : 0.0;
    workoutDataPoint.max_speed = jsonObject.contains("max_speed") ? jsonObject["max_speed"].get<double>() : 0.0;
    workoutDataPoint.average_heartrate = jsonObject.contains("average_heartrate") ? jsonObject["average_heartrate"].get<double>() : 0.0;
    workoutDataPoint.max_heartrate = jsonObject.contains("max_heartrate") ? jsonObject["max_heartrate"].get<double>() : 0.0;
    workoutDataPoint.elev_high = jsonObject.contains("elev_high") ? jsonObject["elev_high"].get<double>() : 0.0;
    workoutDataPoint.elev_low = jsonObject.contains("elev_low") ? jsonObject["elev_low"].get<double>() : 0.0;

    workoutDataPoints.push_back(workoutDataPoint);
  }

  return workoutDataPoints;
}

void loadEnvFromFile(const std::string &filename) {
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

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
  size_t newLength = size * nmemb;
  size_t oldLength = s->size();
  try {
    s->resize(oldLength + newLength);
  } catch (std::bad_alloc &e) {
    return 0;
  }

  std::copy((char *)contents, (char *)contents + newLength, s->begin() + oldLength);
  return size * nmemb;
}

nlohmann::json getJsonFromUrl(const std::string &url, const std::string &header, const std::string &postFields)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    if (!postFields.empty()) {
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    }
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for https
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for https
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, header.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return nlohmann::json::parse(readBuffer);
}

std::vector<WorkoutDataPoint> getWorkoutData(const std::string &client_id, const std::string &client_secret, const std::string &refresh_token) {
  std::string postFields = "client_id=" + client_id + "&client_secret=" + client_secret + "&refresh_token=" + refresh_token + "&grant_type=refresh_token&f=json";

  std::string auth_url = "https://www.strava.com/oauth/token";
  std::string activities_url = "https://www.strava.com/api/v3/athlete/activities";
  std::string header = "";

  std::cout << "Requesting Token...\n";
  nlohmann::json res = getJsonFromUrl(auth_url, header, postFields);
  std::string access_token = res["access_token"];

  header = "Authorization: Bearer " + access_token;
  postFields = "per_page=200&page=1";
  nlohmann::json dataset = getJsonFromUrl(activities_url, header);

  std::vector<WorkoutDataPoint> workoutData = convertJsonToVector(dataset);
  //ChartRenderer chartRenderer;
  //chartRenderer.renderChart(workoutData);
	
  return workoutData;
}
