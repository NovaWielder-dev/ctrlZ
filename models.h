#pragma once
#include <vector>
#include <string>

// Defines an action taken on a specific segment
struct Action {
    int segment_id;
    double target_m_s = 0.0;
    double brake_start_m_before_next = 0.0;
};

// Defines a physical piece of the track [cite: 442-451]
struct Segment {
    int id;
    std::string type;
    double length_m = 0.0;
    double radius_m = 0.0;
};

// Defines the car's physical limits [cite: 400-408]
struct Car {
    double max_speed = 0.0;
    double accel = 0.0;
    double brake = 0.0;
    double crawl_constant = 0.0;
    double fuel_tank_capacity = 0.0;
    double initial_fuel_l = 0.0;
    double fuel_consumption = 0.0;
};

// Defines the overall race data
struct Race {
    std::string name;
    int laps;
    double base_pit_stop_time = 0.0;
    double pit_tyre_swap_time = 0.0;
    double pit_refuel_rate = 0.0;
    double corner_crash_penalty = 0.0;
    double pit_exit_speed = 0.0;
    double fuel_soft_cap_limit = 0.0;
    int starting_weather_condition = 0;
    double time_reference = 0.0;
};