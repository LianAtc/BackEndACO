/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClHormiga.h
 * Author: user
 *
 * Created on 5 de diciembre de 2024, 09:57 PM
 */

#ifndef CLHORMIGA_H
#define CLHORMIGA_H
#include <fstream>
using namespace std;
#include "ClPieza.h"
#include "ClBase.h"
class Hormiga {
private:
    list<Pieza>piezas; 
    Stock base;
    float desperdicio;

public:
    Hormiga() : desperdicio(0.0f), base(), piezas() {}
    void insertarPieza(const Pieza& pieza) {
        piezas.push_back(pieza);
    }
    void setDesperdicio(float nuevoDesperdicio) {
        desperdicio = nuevoDesperdicio;
    }
};

#endif /* CLHORMIGA_H */

