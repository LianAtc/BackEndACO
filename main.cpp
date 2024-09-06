#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <string>
#include <vector>
using namespace std;

#include "ClPieza.h"
#include "ClBase.h"
#include "ClSolucion.h"

int main(int argc, char ** argv){
    Pieza pieza;
    Pieza pieza2;
    Solucion solucion;
    pieza.h = 1;
    pieza.id = 1;
    pieza.r = true;
    pieza.w = 10;
    pieza.y = 10;
    solucion.piezas.push_back(pieza);
    pieza2 = solucion.piezas.back();
    cout << pieza2.h << endl;
    
    return 0;
}

