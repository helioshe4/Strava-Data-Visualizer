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
#include <time.h>


// Converts json response from strava api to vector of workout points
std::vector<WorkoutDataPoint> convertJsonToVector(const nlohmann::json &jsonArray);

// loads env variables from .env
void loadEnvFromFile(const std::string &filename);

// handles json response converts to usable format
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);

// gets json response from strava api
nlohmann::json getJsonFromUrl(const std::string &url, const std::string &header, const std::string &postFields = "");

// wrapper that returns all the workouts from user
std::vector<WorkoutDataPoint> getWorkoutData();

#endif
