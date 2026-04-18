#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "models.h"
#include <vector>
#include <string>
#include <cmath>

// Constants
const double GRAVITY = 9.8; // g in m/s^2
const double TYRE_FRICTION_LEVEL1 = 1.18; // Soft tyre in dry weather for Level 1

class PandaOptimizer {
public:
    // Function for Panda to optimize a single segment
    // It takes the current car state, the current segment, and the next segment (for look-ahead)
    // and returns an Action struct with the optimized decisions for the current segment.
    Action optimizeSegment(const Car& car, const Segment& current_segment, const Segment* next_segment);

private:
    // Helper function to calculate max corner speed for Level 1
    double calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment);

    // Helper function to calculate braking distance
    double calculateBrakingDistance(double initial_speed, double final_speed, double deceleration);
};

#endif // OPTIMIZER_H