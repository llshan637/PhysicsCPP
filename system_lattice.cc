#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "system_lattice.h"

using namespace std;

// initialize spins
SPIN spin[number_spins];

void initialize_lattice(void) {
    // set_basis_vectors();
    set_coordinates();
	set_neighbors();
}

// Set spin coordinates
void set_coordinates(void) {
    
    for(int x = 0; x < L; x++){
        for(int y = 0; y < L; y++) {
            int idx = index(x, y);
            spin[idx].number = idx;
            spin[idx].position[0] = x;
            spin[idx].position[1] = y;
            
        }
    }

}

int mod(int x, int m) {
	if (x >= 0 && x < m)
		return x;
	else if (x < 0)
		return m - 1 - mod(-1-x, m);
	else
		return x % m;
}


// Set latice bounds with periodic boundary conditions on a square lattice
void set_neighbors(void) {
    
    for(int i = 0; i < number_spins; i++){
        int x = spin[i].position[0];
        int y = spin[i].position[1];
        
        spin[i].neighbors[0] = &spin[index(mod(x + 1, L), y)];  //from right one, counter-clockwise
        spin[i].neighbors[1] = &spin[index(x, mod(y + 1, L))];
        spin[i].neighbors[2] = &spin[index(mod(x - 1, L), y)];
        spin[i].neighbors[3] = &spin[index(x, mod(y - 1, L))];
    }
    
}
