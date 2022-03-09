
#ifndef __Ising__Model__lattice__
#define __Ising__Model__lattice__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

const double J1 = -1.;

// square lattice length
const int L = 30;
// total number of spins
const int number_spins = L * L;
const int number_neighbors = 4;

class SPIN {
  public:
	int number;
	int position[2];  // physical position of the spin in a cubic unit cell with length 4;
	SPIN *neighbors[number_neighbors];   // 4 nearest neighbors
	int S;  // the value of classical Ising spin, +1 or -1
};

inline int index(int i, int j) {
	return i * L + j;
}

extern SPIN spin[number_spins]; // form a square lattice

void initialize_lattice(void);
void set_coordinates(void);
int mod(int x, int m);
void set_neighbors(void);


#endif /* defined(__Ising__Model__lattice__) */
