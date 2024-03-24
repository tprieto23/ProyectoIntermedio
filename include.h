#pragma once

#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

void cuatro_cuadros_centrados(int Nmol, int size, std::vector<int> & vector, int seed);

void move_particle(int mol, int paso, int size, std::vector<int> & vector);

void evolution(int Nmol, int size, std::vector<int> & vector, int seed, int Nstep);

double entropia(int Nmol, std::vector<int> & vector);

double radius(int Nmol, std::vector<int> & vector, int size);

void with_hole(int size, std:: vector<int> & vector, int seed, int Nstep, int ratio);
