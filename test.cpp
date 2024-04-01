#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch_test_macros.hpp"
#include "include.cpp"
#include "cmath"

TEST_CASE("Entropia calculation is correct", "[entropia]") {
    int Nmol = 10;
    std::vector<int> vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    double entropy = entropia(Nmol, vector); // Calcula la entropía

    // Verifica si la entropía calculada es correcta
    REQUIRE(entropy == Approx(2.30259).epsilon(0.00001));
}

TEST_CASE("Radius calculation is correct", "[radius]") {
    int Nmol = 10;
    int size = 5;
    std::vector<int> vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    double r = radius(Nmol, vector, size); // Calcula el radio

    // Verifica si el radio calculado es correcto
    REQUIRE(r == Approx(4.5).epsilon(0.00001));
}
