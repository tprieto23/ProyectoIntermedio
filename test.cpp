#include "include.h"

int main(int argc, char ** argv)
{
  int Nmol = 400;
  int size = 20;
  int Nstep = 1000000;
  int seed = 0;

  std::mt19937 gen(seed);
  
  std::uniform_int_distribution<> dis_1{0, Nmol - 1};
  std::uniform_int_distribution<> dis_2{0, 4};

  std::vector<int> particles{0};
  particles.resize(Nmol);

  cuatro_cuadros_centrados(Nmol, size, particles, seed);

  for(int ii = 0; ii < Nmol; ++ii)
    {
      std::cout << particles[ii]/size << "\t" << particles[ii]%size << "\n";
    }

  for (int ii = 1; ii <= Nstep; ++ii)
    {
      step(gen, dis_1, dis_2, size, particles, Nmol);
    }
  
  return 0;
}
