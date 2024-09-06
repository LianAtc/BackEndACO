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

class Solucion {
public:
    std::list<Pieza> piezas;
    Base base;            
    float desperdicio;
};

#endif /* CLSOLUCION_H */

