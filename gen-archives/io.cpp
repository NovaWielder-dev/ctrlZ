#include "io.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Mock implementation for loading level data
void TricksterIO::loadLevel(Car& car, std::vector<Segment>& track) {
    // Hardcoded Level 1 data for demonstration
    car = {90.0, 10.0, 20.0, 10.0}; // max_speed, accel, brake, crawl_speed

    track = {
        {1, "straight", 850.0, 0.0},
        {2, "corner", 120.0, 60.0},
        {3, "straight", 850.0, 0.0},
        {4, "corner", 120.0, 60.0},
        {5, "corner", 90.0, 45.0},
        {6, "corner", 140.0, 80.0},
        {7, "straight", 650.0, 0.0},
        {8, "corner", 140.0, 80.0}
    };
    std::cout << "[Trickster] Level data loaded (mocked)." << std::endl;
}

// Mock implementation for writing submission data
void TricksterIO::writeSubmission(const std::vector<Action>& actions) {
    std::ofstream outfile("submission.txt");
    if (!outfile.is_open()) {
        std::cerr << "[Trickster] Error: Could not open submission.txt for writing." << std::endl;
        return;
    }

    outfile << "{\n";
    outfile << "  \"initial_tyre_id\": 1,\n"; // Hardcoded for Level 1
    outfile << "  \"laps\": [\n";
    outfile << "    {\n";
    outfile << "      \"lap\": 1,\n"; // Assuming single lap for this mock
    outfile << "      \"segments\": [\n";

    for (size_t i = 0; i < actions.size(); ++i) {
        const auto& action = actions[i];
        outfile << "        {\n";
        outfile << "          \"id\": " << action.segment_id << ",\n";
        outfile << "          \"type\": \"" << action.segment_type << "\"";
        if (action.segment_type == "straight") {
            outfile << ",\n";
            outfile << "          \"target_m/s\": " << std::fixed << std::setprecision(2) << action.target_m_s << ",\n";
            outfile << "          \"brake_start_m_before_next\": " << std::fixed << std::setprecision(2) << action.brake_start_m_before_next;
        }
        outfile << "\n        }" << (i == actions.size() - 1 ? "" : ",") << "\n";
    }

    outfile << "      ],\n";
    outfile << "      \"pit\": { \"enter\": false }\n";
    outfile << "    }\n";
    outfile << "  ]\n";
    outfile << "}\n";

    outfile.close();
    std::cout << "[Trickster] Submission data written to submission.txt." << std::endl;
}
