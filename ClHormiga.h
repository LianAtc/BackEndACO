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

#include "ClGrafo.h"

class Hormiga {
private:
    list<Pieza> piezas; 
    Base base;
    float desperdicio;
public:
    Hormiga(Base b) : base(b), desperdicio(0) {}
    void agregarPieza(Pieza p) {piezas.push_back(p);}
    float getDesperdicio() const {return desperdicio;}
    void setDesperdicio(float d) {desperdicio = d;}
    list<Pieza> getPiezas() const { return piezas; }
    Base getBase() const { return base; }
    void imprimirSolucion() const {
        cout << "Solución con " << piezas.size() << " piezas cortadas:\n";
        for (const auto& pieza : piezas) {
            pieza.imprimirPieza();
        }
        cout << "Desperdicio total: " << desperdicio << "\n";
    }
};

#endif /* CLHORMIGA_H */

