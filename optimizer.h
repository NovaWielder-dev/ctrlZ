#pragma once
#include "models.h"
#include "physics.h"

class PandaOptimizer {
public:
    Action optimizeSegment(const Car& car, const Segment& current_segment, const Segment* next_segment, double gravity);
};