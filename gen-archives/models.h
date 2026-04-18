#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

// Car struct (Nova's responsibility)
struct Car {
    double max_speed;
    double accel;
    double brake;
    double crawl_speed;
};

// Segment struct (Nova's responsibility)
struct Segment {
    int id;
    std::string type;
    double length_m;
    double radius_m = 0.0; // Only for corners
};

// Action struct to store Panda's decisions (Nova's responsibility)
struct Action {
    int segment_id;
    std::string segment_type;
    double target_m_s = 0.0; // For straights
    double brake_start_m_before_next = 0.0; // For straights
    double max_corner_speed_m_s = 0.0; // For corners
};

#endif // MODELS_H