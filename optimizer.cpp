#include "optimizer.h"
#include <iostream>
#include <iomanip>

StrategyGenerator::StrategyGenerator() {

}

void StrategyGenerator::initialize_example_data() {
    car = {90.0, 10.0, 20.0, 20.0, 10.0, 150.0, 150.0};
    total_laps = 2;

    track = {
        {1, "straight", 850},
        {2, "corner", 120, 60},
        {3, "straight", 850},
        {4, "corner", 120, 60},
        {5, "corner", 90, 45},
        {6, "corner", 140, 80},
        {7, "straight", 650},
        {8, "corner", 140, 80}
    };

    // Tyre Properties (Base Friction Coefficients)
    // Note: Base friction coefficients are implicitly handled by the friction_multipliers and degradation_rates
    // The example in the PDF uses a base_friction_coefficient for calculation, which is not directly in the JSON structure.
    // For now, I'll use the hardcoded values from the previous solution. 
    // A more robust solution would parse these from a configuration or calculate them.

    // Soft Tyres
    tyre_props["Soft"] = {1.0, 
        {{"dry", 1.18}, {"cold", 1.00}, {"light_rain", 0.92}, {"heavy_rain", 0.80}},
        {{"dry", 0.11}, {"cold", 0.09}, {"light_rain", 0.12}, {"heavy_rain", 0.13}}
    };
    // Medium Tyres
    tyre_props["Medium"] = {1.0, 
        {{"dry", 1.08}, {"cold", 0.97}, {"light_rain", 0.88}, {"heavy_rain", 0.74}},
        {{"dry", 0.10}, {"cold", 0.08}, {"light_rain", 0.09}, {"heavy_rain", 0.10}}
    };
    // Hard Tyres
    tyre_props["Hard"] = {1.0, 
        {{"dry", 0.98}, {"cold", 0.92}, {"light_rain", 0.82}, {"heavy_rain", 0.68}},
        {{"dry", 0.07}, {"cold", 0.06}, {"light_rain", 0.07}, {"heavy_rain", 0.08}}
    };
    // Intermediate
    tyre_props["Intermediate"] = {1.0, 
        {{"dry", 0.90}, {"cold", 0.96}, {"light_rain", 1.08}, {"heavy_rain", 1.02}},
        {{"dry", 0.14}, {"cold", 0.11}, {"light_rain", 0.08}, {"heavy_rain", 0.09}}
    };
    // Wet
    tyre_props["Wet"] = {1.0, 
        {{"dry", 0.72}, {"cold", 0.88}, {"light_rain", 1.02}, {"heavy_rain", 1.20}},
        {{"dry", 0.16}, {"cold", 0.12}, {"light_rain", 0.09}, {"heavy_rain", 0.05}}
    };

    available_tyres.push_back({1, "Soft"});
    available_tyres.push_back({4, "Medium"});
    available_tyres.push_back({7, "Hard"});

    weather_cycle = {
        {1, "cold", 1000.0, 0.95, 0.95},
        {2, "light_rain", 3000.0, 0.80, 0.80}
    };
}

double StrategyGenerator::calculate_max_corner_speed(const std::string& compound, double degradation, const std::string& weather, double radius) {
    double base_friction = 0.0;
    if (compound == "Soft") base_friction = 1.8;
    else if (compound == "Medium") base_friction = 1.7;
    else if (compound == "Hard") base_friction = 1.6;
    else if (compound == "Intermediate") base_friction = 1.2;
    else if (compound == "Wet") base_friction = 1.1;
    
    double weather_mult = tyre_props[compound].friction_multipliers[weather];
    double friction = (base_friction - degradation) * weather_mult;
    return sqrt(friction * G * radius) + car.crawl_speed;
}

void StrategyGenerator::generate_strategy() {
    std::cout << "{" << std::endl;
    std::cout << "  \"initial_tyre_id\": 1," << std::endl;
    std::cout << "  \"laps\": [" << std::endl;

    for (int lap = 1; lap <= total_laps; ++lap) {
        std::cout << "    {" << std::endl;
        std::cout << "      \"lap\": " << lap << "," << std::endl;
        std::cout << "      \"segments\": [" << std::endl;

        for (size_t i = 0; i < track.size(); ++i) {
            const auto& seg = track[i];
            std::cout << "        {" << std::endl;
            std::cout << "          \"id\": " << seg.id << "," << std::endl;
            std::cout << "          \"type\": \"" << seg.type << "\"";

            if (seg.type == "straight") {
                // Simple strategy: Target max speed, brake based on next corner
                double next_corner_speed = 30.0; // Default safe speed
                if (i + 1 < track.size() && track[i+1].type == "corner") {
                    next_corner_speed = calculate_max_corner_speed("Soft", 0.0, "dry", track[i+1].radius_m);
                } else if (i + 1 == track.size()) {
                    // End of lap, pit entry or start next lap
                    next_corner_speed = 20.0; 
                }

                double target_speed = car.max_speed;
                // Distance to brake from target_speed to next_corner_speed
                double brake_dist = (target_speed * target_speed - next_corner_speed * next_corner_speed) / (2 * car.brake);
                if (brake_dist > seg.length_m) {
                    brake_dist = seg.length_m;
                    target_speed = sqrt(next_corner_speed * next_corner_speed + 2 * car.brake * seg.length_m);
                }

                std::cout << "," << std::endl;
                std::cout << "          \"target_m/s\": " << std::fixed << std::setprecision(2) << target_speed << "," << std::endl;
                std::cout << "          \"brake_start_m_before_next\": " << std::fixed << std::setprecision(2) << brake_dist << std::endl;
            } else {
                std::cout << std::endl;
            }

            std::cout << "        }" << (i == track.size() - 1 ? "" : ",") << std::endl;
        }

        std::cout << "      ]," << std::endl;
        std::cout << "      \"pit\": {" << std::endl;
        std::cout << "        \"enter\": " << (lap < total_laps && lap % 10 == 0 ? "true" : "false") << "," << std::endl;
        std::cout << "        \"tyre_change_set_id\": 0," << std::endl;
        std::cout << "        \"fuel_refuel_amount_l\": 0" << std::endl;
        std::cout << "      }" << std::endl;
        std::cout << "    }" << (lap == total_laps ? "" : ",") << std::endl;
    }

    std::cout << "  ]" << std::endl;
    std::cout << "}" << std::endl;
}