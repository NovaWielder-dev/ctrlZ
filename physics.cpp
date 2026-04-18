#include "physics.h"
using namespace std;
namespace Physics {
    double calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment, double gravity) {
        double tyre_friction = Tyre_Friction_Base * Dry_Weather_Multiplier;
        return sqrt(tyre_friction * gravity * corner_segment.radius_m) + car.crawl_constant;
    }

   double calculateBrakingDistance(double initial_speed, double final_speed, double deceleration) {
        if (deceleration <= 0) return 0;
        return (initial_speed * initial_speed - final_speed * final_speed) / (2 * deceleration);
    }
}