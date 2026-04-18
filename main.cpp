#include <iostream>
#include "optimizer.h"

int main() {
    StrategyGenerator gen;
    gen.initialize_example_data();
    gen.generate_strategy();
    return 0;
}
