#ifndef PHYSICS_H
#define PHYSICS_H

#include "models.h"
#include <cmath>

// Constants
const double GRAVITY = 9.8; // g in m/s^2
// Base friction for a Soft tyre is 1.8; dry weather multiplier is 1.18.
const double TYRE_FRICTION_LEVEL1 = 1.8 * 1.18; 

namespace Physics {
    // Helper function to calculate max corner speed for Level 1
    double calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment);

    // Helper function to calculate braking distance
    double calculateBrakingDistance(double initial_speed, double final_speed, double deceleration);
}

#endif // PHYSICS_H