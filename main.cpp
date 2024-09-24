#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>

#include "ClPieza.h"
#include "ClBase.h"

#include "ClSolucion.h"

#include "ClNodo.h"
#include "ClArista.h"
#include "ClGrafo.h"

#include "ClHormiga.h"

void AlgoritmoACO(Base base, std::vector<Pieza> piezas, int numHormigas, int maxIter, float alpha, float beta, float rho, int tol) {
}

int main() {
    
    // Valores iniciales del algoritmo ACO
    float alpha = 1.0, beta = 2.0, rho = 0.1;
    int numHormigas = 100;
    int maxIter = 100;
    int tol = 50;
    
    Base base(200, 200); // Pieza cerámica
    // Cortes
    std::vector<Pieza> piezas = { Pieza(1, 100, 50), Pieza(2, 50, 50), Pieza(3, 50, 25), Pieza(4, 50, 50), Pieza(5, 50, 50),
                                  Pieza(6, 50, 50), Pieza(7, 50, 50), Pieza(8, 50, 50), Pieza(9, 50, 50), Pieza(10, 50, 50)};
    
    // AlgoritmoACO(W, H, piezas, nHorm, maxIter, α, β, ρ, tol):
    AlgoritmoACO(base, piezas, numHormigas, maxIter, alpha, beta, rho, tol);
    
    return 0;
}
