
#ifndef IO_H
#define IO_H

#include "models.h"
#include <vector>

// Mock Trickster class for I/O operations
class TricksterIO {
public:
    // Mock function to load level data
    void loadLevel(Car& car, std::vector<Segment>& track);

    // Mock function to write submission data
    void writeSubmission(const std::vector<Action>& actions);
};

#endif // IO_H