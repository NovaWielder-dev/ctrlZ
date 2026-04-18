#include <iostream>
#include <vector>
#include "models.h"
#include "io.h"
#include "optimizer.h"
#include <iostream>

int main() {
    std::cout << "Starting Entelect Grand Prix Simulator..." << std::endl;

    //Initialise containers
    Car my_car;
    Race my_race;
    std::vector<Action> all_actions;

    //Load data from .json
    extractConfig("1.txt", my_car, my_race);
    std::cout << "Data loaded successfully!" << std::endl;

    //Create optimizer
    PandaOptimizer driver;

    //Loop through laps and segments
    


}
