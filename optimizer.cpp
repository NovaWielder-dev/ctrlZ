#include "optimizer.h"
#include <algorithm>
#include <cmath>

using namespace std;

Action PandaStuff::optimizeSegment(
    const Car& car,
    const Segment& current_segment,
    const Segment* next_segment,
    double gravity)
{
    Action action;
    action.segment_id = current_segment.id;

    if (current_segment.type == "corner") {
        action.target_m_s =
            Physics::calculateMaxCornerSpeed(car, current_segment, gravity);

        action.brake_start_m_before_next = 0.0;
        return action;
    }

    action.target_m_s = car.max_speed;

    if (next_segment && next_segment->type == "corner") {

        double cornerSpeed =
            Physics::calculateMaxCornerSpeed(car, *next_segment, gravity);

        double brakeDistance =
            Physics::calculateBrakingDistance(
                action.target_m_s,
                cornerSpeed,
                car.brake
            );

        action.brake_start_m_before_next = brakeDistance;

        if (brakeDistance > current_segment.length_m) {

            double adjustedSpeed =
                sqrt(cornerSpeed * cornerSpeed +
                     2 * car.brake * current_segment.length_m);

            action.target_m_s =
                min(adjustedSpeed, car.max_speed);
        }
    } else {
        action.brake_start_m_before_next = 0.0;
    }

    return action;
}