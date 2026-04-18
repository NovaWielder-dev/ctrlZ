#pragma once
#include "models.h"
#include <string>

void extractConfig(const std::string& filename, Car& car, Race& race);

void writeSubmission(const std::string& filename, const std::vector<Action>& actions, int total_laps);