#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "system_lattice.h"
#include "monte_carlo.h"
#include "data_collection.h"

using namespace std;

int main(int argc, char *argv[]) {
    double temperature = argc > 1 ? atof(argv[1]) : 5.0;
    double range = 0.1;
    double id = 1.;

    cout << "T = " << temperature << endl;

    initialize_random_seed(id);
    initialize_lattice();
//    read_initial_state(); //read spin configurations and lattice elements
    initialize_random_configuration();

    monte_carlo_data data_tracking(temperature);

    int number_data = 10000;  // 20000; // number of data pts per step
    int thermalized_steps = 20000;  // thermalization steps needed for thermal equilibrium
    int number_sweep = 20;     // number of sweeps per datum

    Monte_Carlo_simulation(temperature, range, number_data, thermalized_steps, number_sweep, data_tracking);
    save_spin_map();
    
}

