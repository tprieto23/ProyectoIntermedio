#include <iostream>
#include "include.h"
#include <fstream>
#include <vector>

int main(void)
{
  ////////////////////////////////////////////////////////////////////////
  //////////////////////// 1st point /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////
  
  int Nmol = 0;
  int size = 0;
  int Nstep = 0;
  int seed = 0;

  //Lectura desde el archivo input.txt
  std::ifstream input;
  input.open("input.txt");
  input >> Nmol >> size >> Nstep >> seed;//40 20 1000000 0
  input.close();
  
  //Las componentes del vector contienen las posiciones
  //de cada particula
  std::vector<int> particles{0}; //inicializa el vector
  particles.resize(Nmol);
  
  //Ubica las particulas aleatoriamente en su distribucion inicial
  //cerca al centro de la taza
  cuatro_cuadros_centrados(Nmol, size, particles, seed);
  
  std::ofstream output1;
  output1.open("1.txt");
  
  //Se realizan todos los pasos de la difusion y en cada uno se
  //imprime el paso, la entropia total y el radio de difusion
  evolution(Nmol, size, particles, seed, Nstep, output1, 1);

  output1.close();

  ////////////////////////////////////////////////////////////////////////
  //////////////////////// 2nd point /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////
  
  std::ifstream input2;
  input2.open("input.txt");
  input2 >> Nmol >> size >> Nstep >> seed;//40 20 1000000 0
  input2.close();
  
  particles = {0};
  particles.resize(Nmol);
  
  cuatro_cuadros_centrados(Nmol, size, particles, seed);
  
  int t = find_t_eq(Nmol, size, particles, seed, Nstep);
  
  std::ofstream output2("2.txt", std::ios::out);
  
  output2 << size << "\t" << t << "\n";
  
  for(int ii = size+1; ii < 40; ++ii)
    {
      particles = {0};
      particles.resize(Nmol);
      cuatro_cuadros_centrados(Nmol, ii, particles, seed);	
      t = find_t_eq(Nmol, ii, particles, seed, Nstep);
      //print_results(output2, ii, t);
      output2 << ii << "\t" << t << "\n";
    }

  output2.close();

  ////////////////////////////////////////////////////////////////////////
  //////////////////////// 4th point /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  int ratio = 0;
  //Lectura desde el archivo input.txt
  std::ifstream input4;
  input4.open("input4.txt");
  input4 >> Nmol >> size >> Nstep >> seed >> ratio;
  input4.close();
  
  //Las componentes del vector contienen las posiciones
  //de cada particula
  particles = {0};
  particles.resize(Nmol);

  //Ubica las particulas aleatoriamente en su distribucion inicial
  //cerca al centro de la taza
  cuatro_cuadros_centrados(Nmol, size, particles, seed);

  std::ofstream output4("4.txt", std::ios::out);

  //Se realizan todos los pasos de la difusion y en cada uno se
  //imprime el paso, la entropia total y el radio de difusion
  with_hole(size, particles, seed, Nstep, ratio, output4);

  output4.close();  
  
  return 0;
}
