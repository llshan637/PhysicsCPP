#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "system_lattice.h"
#include "data_collection.h"

// set the interaction strength J between spins in the system.
extern const double J1;
const double PI = acos(-1.0);

void initialize_random_seed(int id = 1);

inline double random_generator(void) {
	return drand48();
}

void Monte_Carlo_simulation(double T, double range, long int n_data, int thermalized_steps, int number_data, monte_carlo_data & accumulated_data);
void initialize_random_configuration(void);
void read_initial_state(void);
double E_J(void);

inline double E_tot(void) {
    return E_J();
}

void update_spin(int t, double beta, double range);
void sweep(double beta, double range);

