// Monte-Carlo simulation for Ising model.  

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "system_lattice.h"
#include "data_collection.h"
#include "monte_carlo.h"


void initialize_random_seed(int id) {
	time_t seconds;
	time(&seconds);
	srand48(seconds * id);
}

void Monte_Carlo_simulation(double T, double range, long int number_data, int thermalized_steps, int number_sweep, monte_carlo_data &data_tracking){
    double beta;
    monte_carlo_data curr_data(T);
    cout << "Exchange Interaction Density = " << E_J() / number_spins << endl;

    int nth_save = 1000; 
    beta = 1. / T;

    std::ofstream curr_fill;
    curr_fill.open("record.dat");
    curr_fill.close();

    for (int n = 0; n < thermalized_steps; n++) {
        if (n % nth_save == 0) {
            cout << "n-th = " << n << endl;

            curr_data.reset();
            curr_data.energy_computation();
            curr_data.add_data("record.dat", 1. / beta);
        }

        for (int j = 0; j < number_sweep; j++)
            sweep(beta, range);

    }

    int n_save = number_data / 10;

    for (int n = 0; n < number_data; n++) {
        monte_carlo_data instant_data(T);

        for (int m = 0; m < number_sweep; m++)
            sweep(beta, range);
        
        instant_data.energy_computation();
        average_data(data_tracking, instant_data, n);

        if (n  == number_data - 1) {
            data_tracking.save_parameters("final_data.dat", T);
            char spin_filename[30];
            sprintf(spin_filename, "spin_%d.dat", n);
            save_spin_data(spin_filename);
        }
    }

    // saving spin configurations of the Ising model
    save_spin_map();

}


void read_initial_state(void) {
    FILE *fileP;
    fileP = fopen("spin.dat", "r");

    for (int i = 0; i < number_spins; i++) {
        int m;
        int a, b, c;

        fscanf(fileP, "%d\t %d\t %d\t %d\t \n", &m, &a, &b, &c);

        spin[i].S = a;
        spin[i].position[0] = b;
        spin[i].position[1] = c;
    }
    fclose(fileP);
    set_neighbors();
}

void initialize_random_configuration(void){
    // randomly assign the spin on the lattice to be 1 or -1
    for (int i = 0; i < number_spins; i++) {
        double probability = random_generator();

        if (probability >= 0.1) {
            spin[i].S = 1; 
        } else {
            spin[i].S = -1;
        }
    }

}

double E_J(void) {
    double sum = 0;
    for (int i = 0; i < number_spins; i++) {
        for (int r = 0; r < number_neighbors; r++) 
            sum += J1 * spin[i].S * spin[i].neighbors[r]->S;
    }
    return 0.5 * sum;
}

void sweep(double beta, double range) {
    for (int i = 0; i < number_spins; i++) 
        update_spin(i, beta, range);
}

// metropolis algorithm to flip spins
void update_spin(int t, double beta, double range) {
    double probability = random_generator();
    int S_new = spin[t].S;
    double delta_E;

    // flip the spin
    if (probability < range)
        S_new *= -1;
    
    double delta_S = S_new - spin[t].S;
    delta_E = 0;

    for (int i = 0; i < number_neighbors; i++) 
        delta_E += J1 * delta_S * spin[t].neighbors[i]->S;
    
    double prob = random_generator();

    if (prob < exp(-beta * delta_E)) 
        spin[t].S = S_new;

}


