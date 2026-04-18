#pragma once
#include "models.h"
#include <cmath>
const double Tyre_Friction_Base = 1.8; 
const double Dry_Weather_Multiplier = 1.18;

namespace Physics {
    double calculateMaxCornerSpeed(const Car& car, const Segment& corner_segment, double gravity);
    double calculateBrakingDistance(double initial_speed, double final_speed, double deceleration);
}