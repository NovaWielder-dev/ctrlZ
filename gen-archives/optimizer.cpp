#include "optimizer.h"
#include <algorithm>

// Helper function to calculate max corner speed for Level 1
double PandaOptimizer::calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment) {
    // Formula: Max Corner Speed = sqrt(tyre_friction * 9.8 * radius) + crawl_constant_m/s
    // Assume tyre friction is 1.18 for the Soft tyre in dry weather (Level 1)
    return std::sqrt(TYRE_FRICTION_LEVEL1 * GRAVITY * corner_segment.radius_m) + car.crawl_speed;
}

// Helper function to calculate braking distance
double PandaOptimizer::calculateBrakingDistance(double initial_speed, double final_speed, double deceleration) {
    // Formula: Distance = (initial_speed^2 - final_speed^2) / (2 * deceleration)
    // This formula assumes initial_speed > final_speed for braking.
    if (deceleration <= 0) return 0; // Avoid division by zero or non-physical deceleration
    return (initial_speed * initial_speed - final_speed * final_speed) / (2 * deceleration);
}

// Function for Panda to optimize a single segment
Action PandaOptimizer::optimizeSegment(const Car& car, const Segment& current_segment, const Segment* next_segment) {
    Action action;
    action.segment_id = current_segment.id;
    action.segment_type = current_segment.type;

    if (current_segment.type == "straight") {
        // For straights, output target_m/s (usually the car's absolute maximum speed)
        action.target_m_s = car.max_speed;

        // Braking Logic: Look one step ahead to the next segment
        if (next_segment && next_segment->type == "corner") {
            double next_corner_max_speed = calculateMaxCornerSpeed(car, *next_segment);
            double braking_distance_needed = calculateBrakingDistance(action.target_m_s, next_corner_max_speed, car.brake);
            
            // If the required braking distance is greater than the straight's length,
            // we cannot reach car.max_speed and brake safely. Adjust target_m_s.
            if (braking_distance_needed > current_segment.length_m) {
                // Calculate the maximum speed we can reach on this straight
                // such that we can still brake within the straight's length.
                // V_target_new^2 = V_corner_max^2 + 2 * car.brake * current_segment.length_m
                double adjusted_target_speed = std::sqrt(next_corner_max_speed * next_corner_max_speed + 2 * car.brake * current_segment.length_m);
                action.target_m_s = std::min(adjusted_target_speed, car.max_speed); // Ensure it doesn't exceed max_speed
                action.brake_start_m_before_next = current_segment.length_m; // Brake at the very end of the straight
            } else {
                action.brake_start_m_before_next = braking_distance_needed;
            }
        } else {
            // If no next segment or next segment is not a corner, no braking is needed for a corner.
            // We can maintain max speed throughout the straight.
            action.brake_start_m_before_next = 0.0; // Or some other default if needed, e.g., for end of race
        }
    } else if (current_segment.type == "corner") {
        // For corners, calculate the maximum safe speed
        action.max_corner_speed_m_s = calculateMaxCornerSpeed(car, current_segment);
    }
    return action;
}
