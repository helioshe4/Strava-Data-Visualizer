#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "workoutdatapoint.h"

/*
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

  // todo decide which other data points to add
  double average_speed;
  double max_speed;
  //bool has_heartrate;
  double average_heartrate;
  double max_heartrate;
  double elev_high;
  double elev_low;
};
*/

std::vector<WorkoutDataPoint> convertJsonToVector(const nlohmann::json &jsonArray);
void loadEnvFromFile(const std::string &filename);
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);
nlohmann::json getJsonFromUrl(const std::string &url, const std::string &header, const std::string &postFields = "");

#endif
