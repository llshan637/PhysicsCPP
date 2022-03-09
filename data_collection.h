//  Data analysis for Ising model 

#ifndef __Ising__Model__analysis__
#define __Ising__Model__analysis__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "system_lattice.h"

using namespace std;

class monte_carlo_data {
  public:
    double beta;
    int steps;
    double E;
    double pow_E;
    
    monte_carlo_data(double T) {
        beta = 1. / T;
        reset();
    };

    void reset(void) {
        steps = 0;
        E = 0;
    }

    void energy_computation(void);
    
    void save_parameters(string const filename, double parameter) {
        std::ofstream curr_file;
        curr_file.open(filename.c_str(), std::ios::out);

        curr_file.precision(8);
        curr_file << parameter << '\t';
        curr_file << E / ((double)number_spins) << '\t';
        // keep records of heat capacity
        curr_file << beta * beta * (pow_E - pow(E, 2)) / ((double)number_spins) << '\t';
        curr_file << steps << '\t';
        curr_file << endl;
        curr_file.close();
    };

    void add_data(string const filename, double parameter) {
        std::ofstream curr_file;
        curr_file.open(filename.c_str(), std::ofstream::out | std::ofstream::app);

        curr_file.precision(8);
        curr_file << parameter << '\t';
        curr_file << E / ((double)number_spins) << '\t';
        curr_file << beta * beta * (pow_E - pow(E, 2)) / ((double)number_spins) << '\t';
        curr_file << steps << '\t';
        curr_file << endl;
        curr_file.close();
    }
    
};

void average_data(monte_carlo_data &accumulated_data, monte_carlo_data &curr_data, int counts);
void save_spin_data(char* filename);
void save_spin_map(void);

#endif /* defined(__Ising__Model__analysis__) */
