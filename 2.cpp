#include <iostream>
#include "include.h"
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
    int Nmol = 0;
    int size = 0;
    int Nstep = 0;
    int seed = 0;

    //Lectura desde el archivo input.txt
    std::ifstream input;
    input.open("input.txt");
    input >> Nmol >> size >> Nstep >> seed;//40 20 1000000 0
    input.close();

    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);

    cuatro_cuadros_centrados(Nmol, size, particles, seed);

    int t = find_t_eq(Nmol, size, particles, seed, Nstep);

    std::cout << size << "\t" << t << "\n";

    for(int ii = size+1; ii < 40; ++ii)
      {
	particles = {0};
	particles.resize(Nmol);
	cuatro_cuadros_centrados(Nmol, ii, particles, seed);	
	t = find_t_eq(Nmol, ii, particles, seed, Nstep);
	std::cout << ii << "\t" << t << "\n";
	
      }

    return 0;
}
