#include "include.h"
#include <iostream>

void cuatro_cuadros_centrados(int Nmol, int size, std::vector<int> &vector, int seed)
{
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis{0, 1};
  int esquina = (size - 1) / 2;
  for (int n = 0; n < Nmol; n++) {
    int i = 0, j = 0;
    i = esquina + dis(gen);
    j = esquina + dis(gen);
    vector[n] = i * size + j;
  }
}

void move_particle(int mol, int paso, int size, std::vector<int> & vector)
{
  switch(paso) {
  case 1:
    if (vector[mol] / size != 0)
      vector[mol] += -size; // arriba
    else
      vector[mol] += (size - 1) * size; // se teletransporta hacia la pared de abajo
    break;
  case 2:
    if (vector[mol] / size != size - 1)
      vector[mol] += size; // abajo
    else
      vector[mol] = vector[mol] % size; // se teletransporta hacia la pared de arriba
    break;
  case 3:
    if (vector[mol] % size != 0)
      vector[mol] += -1; // izquierda camarada
    else
      vector[mol] += size - 1; // se teletransporta hacia la pared derecha
    break;
  case 4:
    if (vector[mol] % size != size - 1)
      vector[mol] += 1; // le voy a dar en la cara marica
    else
      vector[mol] = vector[mol] / size; // se teletransporta hacia la pared izquierda
    break;
  }
}

void evolution(int Nmol, int size, std::vector<int> & vector, int seed, int Nstep) {
  if (Nmol != 0) {
    std::mt19937 gen(seed);
    
    int mol = 0;
    std::uniform_int_distribution<> dis_1{0, Nmol - 1};

    int paso = 0;
    std::uniform_int_distribution<> dis_2{0, 4};
    
    std::cout.precision(6);
    std::cout << 0 << "\t" << entropia(Nmol, vector) << "\n";
    
    for (int ii = 1; ii <= Nstep; ++ii) {
      mol = dis_1(gen);
      paso = dis_2(gen);
      move_particle(mol, paso, size, vector);
      
      std::cout << ii << "\t" << entropia(Nmol, vector) << "\t"
                << radius(Nmol, vector, size) << "\n";
    }
  }
}

// Calcula la entropia de cierta configuracion de las particulas
double entropia(int Nmol, std::vector<int> &vector) {
  std::sort(vector.begin(),
            vector.end()); // ordena los valores del vector para que los que son
                           // iguales queden contiguos
  double sum = 0;
  double aux = 1;
  for (int ii = 0; ii < Nmol - 1; ++ii) {
    if (vector[ii] != vector[ii + 1]) {
      aux = aux / Nmol;
      sum -= aux * (std::log(aux));
      aux = 1;
    } else {
      aux += 1;
    }
  }
  aux = aux / Nmol;
  sum -= aux * (std::log(aux));
  return sum;
}

// Calcula el radio de difusion de la crema de cafe
double radius(int Nmol, std::vector<int> &vector, int size) {
  double r = 0;
  for (int ii = 0; ii < Nmol; ++ii) {
    int x = (vector[ii] / size) - ((size - 1) / 2);
    int y = (vector[ii] % size) - ((size - 1) / 2);
    r += std::pow(x - 0.5, 2) + std::pow(y - 0.5, 2);
  }
  r = r / Nmol;
  return std::sqrt(r);
}

void with_hole(int size, std::vector<int> &vector, int seed, int Nstep,
               int ratio) {
  std::mt19937 gen(seed); // OJO: de pronto se generan los numeros aleatorios 3 veces
  int numero = static_cast<int>(vector.size());
  std::uniform_int_distribution<> dis_1{0, numero - 1};
  int mol = 0;
  std::uniform_int_distribution<> dis_2{0, 4};
  int paso = 0;
  for (int ii = 1; ii <= Nstep; ++ii) {
    if (numero == 0)
      break;
    mol = dis_1(gen);
    if (mol > numero - 1) {
      continue;
    } // Se siguen contando pasos por las moleculas afuera
    paso = dis_2(gen);
    if (paso == 1) {
      if (vector[mol] / size != 0)
        vector[mol] += -size; // arriba
      else
        vector[mol] += (size - 1) * size; // Se teletransporta
    } else if (paso == 2) {
      if (vector[mol] / size != size - 1)
        vector[mol] += size; // abajo
      else {
        vector[mol] = vector[mol] % size; // se tp
      }
    } else if (paso == 3) {
      if (vector[mol] % size != 0)
        vector[mol] += -1; // izquierda camarada
      else
        vector[mol] += size - 1; // se tp
    } else if (paso == 4) {
      if (vector[mol] % size != size - 1)
        vector[mol] += 1; // le voy a dar en la cara marica
      else {
        if ((size - 1 - size / ratio) <= vector[mol] / size <= size - 1) {
          vector.erase(vector.begin() + mol); // sale por la derecha
          numero = static_cast<int>(vector.size());
        } else
          vector[mol] = vector[mol] / size; // se tp
      }
    }
    std::cout << ii << "\t" << numero << "\n";
  }
}
