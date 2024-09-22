/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClHormiga.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 22 de septiembre de 2024, 01:20 PM
 */

#ifndef CLHORMIGA_H
#define CLHORMIGA_H
#include <fstream>
using namespace std;

class Hormiga {
private:
    Solucion solucion;
    std::list<Pieza> piezasPendientes;

public:
    Hormiga(Solucion sol) : solucion(sol) {}

    void agregarPiezaPendiente(Pieza pieza) {
        piezasPendientes.push_back(pieza);
    }

    void imprimirHormiga() const {
        std::cout << "Hormiga - Solución: " << std::endl;
        solucion.imprimirSolucion();
        std::cout << "Piezas pendientes:" << std::endl;
        for (const auto& pieza : piezasPendientes) {
            pieza.imprimirPieza();
        }
    }
};

#endif /* CLHORMIGA_H */

