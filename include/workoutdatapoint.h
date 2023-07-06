// workoutdatapoint.h
#ifndef WORKOUTDATAPOINT_H
#define WORKOUTDATAPOINT_H

#include <string>
#include <ctime>

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
//	struct tm start_date;
    std::string start_date_local;
    std::string timezone;
    std::string location_city;
    std::string location_state;
    std::string location_country;
    double average_speed;
    double max_speed;
    bool has_heartrate;
    double average_heartrate;
    double max_heartrate;
    double elev_high;
    double elev_low;
};

#endif // WORKOUTDATAPOINT_H
