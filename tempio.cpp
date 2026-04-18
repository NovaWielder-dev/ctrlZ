#include "io.h"
#include <fstream>
#include <iostream>
#include "json.hpp" // Ensure you downloaded json.hpp to your folder

using json = nlohmann::json;

void extractConfig(const std::string& filename, Car& car, Race& race) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "CRITICAL ERROR: Could not open " << filename << std::endl;
        return;
    }

    json data;
    file >> data;

    // 1. Extract Car Data
    car.max_speed = data["car"]["max_speed_m/s"];
    car.accel = data["car"]["accel_m/se2"];
    car.brake = data["car"]["brake_m/se2"];
    car.crawl_constant = data["car"]["crawl_constant_m/s"];
    car.fuel_tank_capacity = data["car"].value("fuel_tank_capacity_l", 0.0);
    car.initial_fuel_l = data["car"].value("initial_fuel_l", 0.0);
    car.fuel_consumption = data["car"].value("fuel_consumption_l/m", 0.0);

    // 2. Extract Race Data
    race.name = data["race"]["name"];
    race.laps = data["race"]["laps"];
    race.base_pit_stop_time = data["race"].value("base_pit_stop_time_s", 0.0);
    race.pit_tyre_swap_time = data["race"].value("pit_tyre_swap_time_s", 0.0);
    race.pit_refuel_rate = data["race"].value("pit_refuel_rate_l/s", 0.0);
    race.corner_crash_penalty = data["race"].value("corner_crash_penalty_s", 0.0);
    race.pit_exit_speed = data["race"].value("pit_exit_speed_m/s", 0.0);
    race.fuel_soft_cap_limit = data["race"].value("fuel_soft_cap_limit_l", 0.0);
    race.starting_weather_condition = data["race"].value("starting_weather_condition_id", 1);
    race.time_reference = data["race"].value("time_reference_s", 0.0);

    // 3. Extract Track Segments
    for (const auto& item : data["track"]["segments"]) {
        Segment seg;
        seg.id = item["id"];
        seg.type = item["type"];
        
        // Only load length if it exists
        if (item.contains("length_m")) {
            seg.length_m = item["length_m"];
        }
        
        // Only load radius if it exists
        if (item.contains("radius_m")) {
            seg.radius_m = item["radius_m"];
        }

        race.segments.push_back(seg);
    }
}