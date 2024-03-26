#include "include.h"
#include <iostream>

void cuatro_cuadros_centrados(int Nmol, int size, std::vector<int> &vector, int seed)
{
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis{0, 1};
  int esquina = size/2 - 1;
  for (int n = 0; n < Nmol; n++) {
    int i = 0, j = 0;
    i = esquina + dis(gen);
    j = esquina + dis(gen);
    vector[n] = i*size + j;
  }
}

void move_particle(int mol, int paso, int size, std::vector<int> & vector)
{
  switch(paso) {
  case 1:
    (vector[mol]/size != 0) ? (vector[mol] -= size) : (vector[mol] += (size - 1) * size);
    break;
  case 2:
    (vector[mol]/size != size - 1) ? (vector[mol] += size) : (vector[mol] = vector[mol]%size);
    break;
  case 3:
    (vector[mol] % size != 0) ? (vector[mol] -= 1) : (vector[mol] += size - 1);
    break;
  case 4:
    (vector[mol] % size != size - 1) ? (vector[mol] += 1) : (vector[mol] = size * (vector[mol] / size));
    break;
  }
}

void step(std::mt19937 & gen, std::uniform_int_distribution<> & dis_1, std::uniform_int_distribution<> & dis_2, int size, std::vector<int> & vector)
{
  int mol = dis_1(gen);
  int paso = dis_2(gen);
  move_particle(mol, paso, size, vector);
}

int find_t_eq(int Nmol, int size, std::vector<int> & vector, int seed, int Nstep)
{
  std::mt19937 gen(seed);
  
  std::uniform_int_distribution<> dis_1{0, Nmol - 1};
  std::uniform_int_distribution<> dis_2{1, 4};
  
  for (int ii = 1; ii <= Nstep; ++ii)
    {
      step(gen, dis_1, dis_2, size, vector);
      int aux = ((entropia(Nmol, vector) < 0.75*std::log((size - 1)*size)) ? 0 : 1);
      switch(aux)
	{
	case 0:
	  break;
	case 1:
	  return ii;
	}
    }
}

void evolution(int Nmol, int size, std::vector<int> & vector, int seed, int Nstep)
{
  std::mt19937 gen(seed);
  
  std::uniform_int_distribution<> dis_1{0, Nmol - 1};
  std::uniform_int_distribution<> dis_2{0, 4};
  
  std::cout.precision(6);
  std::cout << 0 << "\t" << entropia(Nmol, vector) << "\n";
  
  for (int ii = 1; ii <= Nstep; ++ii) {
    step(gen, dis_1, dis_2, size, vector);
    if(ii%100 == 0)
    {
      std::cout << ii << "\t"
		<< entropia(Nmol, vector) << "\t"
		<< radius(Nmol, vector, size) << "\n";
    }
  }
}

double entropia(int Nmol, std::vector<int> & vector) {
  
  std::sort(vector.begin(), vector.end());

  double sum = 0;
  double aux = 1;
  
  for (int ii = 0; ii < Nmol; ++ii) {
    if(ii != (Nmol - 1))
      {
	if (vector[ii] != vector[ii + 1])
	  {
	    aux = aux / Nmol;
	    sum -= aux * (std::log(aux));
	    aux = 1;
	  }
	else
	  {
	    aux += 1;
	  }
      }
    else
      {
	aux = aux/Nmol;
	sum -= aux*(std::log(aux));
      }
  }
  return sum;
}

double radius(int Nmol, std::vector<int> & vector, int size)
{
  double r = 0.0;
  for (int ii = 0; ii < Nmol; ++ii)
    {
      int x = (vector[ii]/size) - (size/2) + 1;
      int y = (vector[ii]%size) - (size/2) + 1;
      r += std::pow(x, 2) + std::pow(y, 2);
    }
  r = r/Nmol;
  return std::sqrt(r);
}

void with_hole(int size, std::vector<int> &vector, int seed, int Nstep, int ratio)
{
  std::mt19937 gen(seed);
  int numero = vector.size();
  std::uniform_int_distribution<> dis_1{0, numero - 1};
  int mol = 0;
  std::uniform_int_distribution<> dis_2{0, 4};
  int paso = 0;
  for (int ii = 1; ii <= Nstep; ++ii) {
    mol = dis_1(gen);
    if (numero == 0)
      {
	break;
      }
    if(mol > numero - 1)
      {
	continue;
      } // Se siguen contando pasos por las moleculas afuera
    paso = dis_2(gen);
    switch(paso)
      {
      case 1:
	(vector[mol] / size != 0) ? (vector[mol] += -size) : (vector[mol] += (size - 1) * size);
	break;
      case 2:
	(vector[mol] / size != size - 1) ? (vector[mol] += size) : (vector[mol] = vector[mol] % size);
	break;
      case 3:
	(vector[mol] % size != 0) ? (vector[mol] += -1) : (vector[mol] += size - 1);
	break;
      case 4:
	if (vector[mol] % size != size - 1)
	  vector[mol] += 1; // le voy a dar en la cara marica
	else
	  {
	    if ((size - 1 - size / ratio) <= vector[mol] / size <= size - 1)
	      {
		vector.erase(vector.begin() + mol); // sale por la derecha
		numero = vector.size();
	      }
	    else
	      vector[mol] = size * (vector[mol] / size);
	  }
	break;
      }
    std::cout << ii << "\t" << numero << "\n";
  }
}
