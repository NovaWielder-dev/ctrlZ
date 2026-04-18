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

void writeSubmission(const std::string& filename, const std::vector<Action>& actions, int total_laps) {
    // 1. Create the master JSON object and hardcode the Level 1 tyre
    json submission;
    submission["initial_tyre_id"] = 1;

    // Figure out how many segments are in a single lap
    int segments_per_lap = actions.size() / total_laps;
    
    json laps_array = json::array();

    // 2. Loop through each lap
    for (int lap = 0; lap < total_laps; ++lap) {
        json lap_obj;
        
        // Hardcode no pit stops for Level 1
        lap_obj["pit"]["enter"] = false;

        // 3. Loop through the segments for THIS specific lap
        json segments_array = json::array();
        for (int s = 0; s < segments_per_lap; ++s) {
            
            // Calculate where we are in the master flat list
            int index = (lap * segments_per_lap) + s;
            const Action& current_action = actions[index];

            // Build the segment object
            json seg_obj;
            seg_obj["id"] = current_action.segment_id;
            seg_obj["target_speed_m/s"] = current_action.target_m_s;
            seg_obj["brake_start_m_before_next_segment"] = current_action.brake_start_m_before_next;
            
            segments_array.push_back(seg_obj);
        }
        
        // Attach the segments to the lap, and the lap to the master array
        lap_obj["segments"] = segments_array;
        laps_array.push_back(lap_obj);
    }

    submission["laps"] = laps_array;

    // 4. Save to the hard drive
    std::ofstream file(filename);
    if (file.is_open()) {
        file << submission.dump(4); // .dump(4) adds nice spacing
        std::cout << "SUCCESS: Wrote " << actions.size() << " actions to " << filename << std::endl;
    } else {
        std::cerr << "CRITICAL ERROR: Could not create " << filename << std::endl;
    }
}