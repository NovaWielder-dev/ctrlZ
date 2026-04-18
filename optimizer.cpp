#include "optimizer.h"
#include <algorithm>
#include <cmath>

using namespace std;

Action PandaOptimizer::optimizeSegment(
    const Car& car,
    const Segment& current_segment,
    const Segment* next_segment,
    double gravity)
{
    Action action;
    action.segment_id = current_segment.id; // assign current segment

    // If we're in a corner: just take safe corner speed
    if (current_segment.type == "corner") {
        action.target_m_s =
            Physics::calculateMaxCornerSpeed(car, current_segment, gravity);

        action.brake_start_m_before_next = 0.0;
        return action;
    }

    // Otherwise assume straight → go max speed
    action.target_m_s = car.max_speed;

    // Check if a corner is coming next
    if (next_segment && next_segment->type == "corner") {

        // Safe speed for upcoming corner
        double cornerSpeed =
            Physics::calculateMaxCornerSpeed(car, *next_segment, gravity);

        // Distance needed to slow down
        double brakeDistance =
            Physics::calculateBrakingDistance(
                action.target_m_s,
                cornerSpeed,
                car.brake
            );

        action.brake_start_m_before_next = brakeDistance;

        // If not enough space → reduce speed
        if (brakeDistance > current_segment.length_m) {

            // Adjust speed using physics equation
            double adjustedSpeed =
                sqrt(cornerSpeed * cornerSpeed +
                     2 * car.brake * current_segment.length_m);

            action.target_m_s =
                min(adjustedSpeed, car.max_speed);
        }
    }
    else {
        // No upcoming corner → no braking needed
        action.brake_start_m_before_next = 0.0;
    }

    return action;
}