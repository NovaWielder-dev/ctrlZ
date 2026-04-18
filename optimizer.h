#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "models.h"
#include "physics.h"
#include <vector>
#include <string>
#include <cmath>

class PandaOptimizer {
public:
    // Function for Panda to optimize a single segment
    // It takes the current car state, the current segment, and the next segment (for look-ahead)
    // and returns an Action struct with the optimized decisions for the current segment.
    Action optimizeSegment(const Car& car, const Segment& current_segment, const Segment* next_segment);
};

#endif // OPTIMIZER_H