#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "system_lattice.h"
#include "monte_carlo.h"
#include "data_collection.h"


void average_data(monte_carlo_data &accumulated_data, monte_carlo_data &curr_data, int count) {
    if (count == 0) {
        accumulated_data.reset();
    }
    accumulated_data.E = (count * accumulated_data.E + curr_data.E) / (count + 1.);
    accumulated_data.pow_E = (count * accumulated_data.pow_E + curr_data.pow_E) / (count + 1.);
    accumulated_data.steps = count;
}


void monte_carlo_data::energy_computation(void) {
    E = E_tot();
    pow_E = pow(E, 2);
}

void save_spin_map(void) {
    std::ofstream curr_file;
    curr_file.open("spin_map.dat", std::ios::out);
    curr_file.precision(8);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            int index = i * L + j;
            curr_file << spin[index].S << '\t';
        }
        curr_file << '\n';
    }
    curr_file.close();
}

void save_spin_data(char *filename) {
    FILE *curr_file = fopen(filename, "w");
    for (int i = 0; i < number_spins; i++) {
        fprintf(curr_file, "%d\t %d\t %d\t %d\t \n", i, spin[i].S, spin[i].position[0], spin[i].position[1]);
    }
    fclose(curr_file);
}

