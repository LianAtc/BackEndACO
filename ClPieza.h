/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClPieza.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 5 de septiembre de 2024, 10:54 PM
 */

#ifndef CLPIEZA_H
#define CLPIEZA_H
#include <fstream>
using namespace std;

class Pieza {
private:
    int id;
    float x, y;
    float w, h;
    bool r;
public:
    Pieza(int id, float x, float y, float w, float h, bool r) : id(id), x(x), y(y), w(w), h(h), r(r) {}
    int getId() const { return id; }
    std::pair<float, float> getPosition() const { return {x, y}; }
    float getAncho() const { return w; }
    float getAlto() const { return h; }
    float area() const { return w * h; }
    void imprimirPieza() const {
        std::cout << "Pieza ID: " << id << ", Posición: (" << x << ", " << y
                  << "), Dimensiones: (" << w << ", " << h << "), Rotada: " << (r ? "Sí" : "No") << std::endl;
    }
};

#endif /* CLPIEZA_H */

