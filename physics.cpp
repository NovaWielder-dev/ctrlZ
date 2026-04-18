#include "physics.h"

namespace Physics {
    // Helper function to calculate max corner speed for Level 1
    double calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment) {
        // Formula: Max_Speed = square_root(tyre_friction * 9.8 * radius) + crawl_constant_m/s
        return std::sqrt(TYRE_FRICTION_LEVEL1 * GRAVITY * corner_segment.radius_m) + car.crawl_speed;
    }

    // Helper function to calculate braking distance
    double calculateBrakingDistance(double initial_speed, double final_speed, double deceleration) {
        // Formula: Distance = (Initial_Speed^2 - Final_Speed^2) / (2 * Car.brake)
        // This formula assumes initial_speed > final_speed for braking.
        if (deceleration <= 0) return 0; // Avoid division by zero or non-physical deceleration
        return (initial_speed * initial_speed - final_speed * final_speed) / (2 * deceleration);
    }
}
