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
    // Inicialización
    Pieza(int id_, float w_, float h_) : id(id_), w(w_), h(h_), x(0), y(0), r(false) {}
    // Obtener valores (privados)
    int getId() const { return id; }
    std::pair<float, float> getPosition() const { return {x, y}; }
    float getAncho() const { return w; }
    float getAlto() const { return h; }
    // Extras
    float area() const { return w * h; }
    // Impresión
    void imprimirPieza() const {
        std::cout << "Pieza ID: " << id << ", Posición: (" << x << ", " << y
                  << "), Dimensiones: (" << w << ", " << h << "), Rotada: " << (r ? "Sí" : "No") << std::endl;
    }
};

#endif /* CLPIEZA_H */

