#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <vector>
#include <string>
#include <cmath>
#include <map>

// Constants from specification
const double G = 9.8;
const double K_STRAIGHT = 0.0000166;
const double K_BRAKING = 0.0398;
const double K_CORNER = 0.000265;
const double K_BASE_FUEL = 0.0005;
const double K_DRAG_FUEL = 0.0000000015;

struct TyreProperty {
    double life_span;
    std::map<std::string, double> friction_multipliers;
    std::map<std::string, double> degradation_rates;
};

struct TyreSet {
    int id;
    std::string compound;
    double current_degradation = 0.0;
};

struct WeatherCondition {
    int id;
    std::string condition;
    double duration_s;
    double accel_multiplier;
    double brake_multiplier;
};

struct Segment {
    int id;
    std::string type;
    double length_m;
    double radius_m = 0.0;
};

struct Car {
    double max_speed;
    double accel;
    double brake;
    double limp_speed;
    double crawl_speed;
    double fuel_capacity;
    double initial_fuel;
};

// Simplified simulator/strategy state
struct RaceState {
    double total_time = 0.0;
    double current_fuel;
    TyreSet current_tyre;
    double current_speed = 0.0;
    int current_lap = 1;
    std::string current_weather = "dry";
};

// Main Strategy Class
class StrategyGenerator {
public:
    Car car;
    std::vector<Segment> track;
    std::map<std::string, TyreProperty> tyre_props;
    std::vector<TyreSet> available_tyres;
    std::vector<WeatherCondition> weather_cycle;
    int total_laps;

    StrategyGenerator(); // Constructor

    void initialize_example_data();
    double calculate_max_corner_speed(const std::string& compound, double degradation, const std::string& weather, double radius);
    void generate_strategy();
};

#endif // OPTIMIZER_H