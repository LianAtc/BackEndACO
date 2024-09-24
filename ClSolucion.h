/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClSolucion.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 5 de septiembre de 2024, 10:56 PM
 */

#ifndef CLSOLUCION_H
#define CLSOLUCION_H
#include <fstream>
#include <list>
using namespace std;

#include "ClBase.h"
#include "ClPieza.h"

class Solucion {
private:
    std::list<Pieza> piezas;
    Base base;
    float desperdicio;

public:
    // Inicialización
    Solucion(Base base) : base(base), desperdicio(0) {}
    void agregarPieza(Pieza pieza) {
        piezas.push_back(pieza);
    }
    // Impresión
    void imprimirSolucion() const {
        std::cout << "Solución:" << std::endl;
        for (const auto& pieza : piezas) {
            pieza.imprimirPieza();
        }
        base.imprimirCortes();
        std::cout << "Desperdicio: " << desperdicio << std::endl;
    }
};

#endif /* CLSOLUCION_H */

