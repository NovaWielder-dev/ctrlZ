#include "physics.h"
using namespace std;

namespace Physics {

    // Calculates maximum safe speed for taking a corner
    double calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment, double gravity) {

        double tyre_friction = Tyre_Friction_Base * Dry_Weather_Multiplier;

        // Physics-based cornering speed + car-specific adjustment
        return sqrt(tyre_friction * gravity * corner_segment.radius_m)
               + car.crawl_constant;
    }

    // Calculates distance needed to slow down from one speed to another
    double calculateBrakingDistance(double initial_speed, double final_speed, double deceleration) {

        // Prevent division by zero or invalid deceleration
        if (deceleration <= 0) return 0;

        // Physics braking equation
        return (initial_speed * initial_speed - final_speed * final_speed)
               / (2 * deceleration);
    }

}