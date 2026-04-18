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
    extractConfig("1.txt");
    std::cout << "Data loaded successfully!" << std::endl;

    //Create optimizer
    PandaOptimizer driver;

    //Loop through laps
    for (int lap = 1; lap <= my_race.total_laps; ++lap) {
        
        //Loop through segments
        for (size_t i = 0; i < my_race.segments.size(); ++i) {
            
            Segment current = my_race.segments[i];

            Segment next;
            if (i + 1 < my_race.segments.size()) {
                next = my_race.segments[i + 1];
            }
            else {
                next = my_race.segments[0];
            }

            Action a = driver.optimizeSegment(my_car, current, next);

            all_actions.push_back(a);
        }
    }

    //[Trickster: Export final JSON]
    //writeSubmission("submission.txt", all_actions);

    std::cout << "Race Complete! Output saved." << std::endl;
    return 0;

}
