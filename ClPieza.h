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
    Pieza(int id, float w, float h, float x = 0, float y = 0, bool r = false)
        : id(id), w(w), h(h), x(x), y(y), r(r) {}
    void rotarPieza() {r = !r;}
    float getWidth() const {return r ? h : w;}
    float getHeight() const {return r ? w : h;}    
    float getX() const { return x; }
    float getY() const { return y; }
    void setPosicion(float px, float py) {
        x = px;
        y = py;
    }
    void imprimirPieza() const {
        cout << "Pieza ID: " << id 
                  << " | Posición: (" << x << ", " << y << ")"
                  << " | Rotacion: (" << r << ")"
                  << " | Dimensiones: (" << w << "x" << h << ")\n";
    }
    void imprimirPiezaRestante() const {
        cout << "Pieza ID: " << id 
                  << " | Dimensiones: (" << w << "x" << h << ")\n";
    }
};


#endif /* CLPIEZA_H */

