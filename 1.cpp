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

    //Las componentes del vector contienen las posiciones
    //de cada particula
    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);

    //Ubica las particulas aleatoriamente en su distribucion inicial
    //cerca al centro de la taza
    cuatro_cuadros_centrados(Nmol, size, particles, seed);

    //Se realizan todos los pasos de la difusion y en cada uno se
    //imprime el paso, la entropia total y el radio de difusion
    evolution(Nmol,size,particles,seed,Nstep);

    return 0;
}
