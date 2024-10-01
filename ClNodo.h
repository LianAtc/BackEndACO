/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClNodo.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 22 de septiembre de 2024, 01:16 PM
 */

#ifndef CLNODO_H
#define CLNODO_H
#include <fstream>
using namespace std;

class Nodo {
private:
    int id;
    float w, h;
    float x, y;
    bool esHoja;
public:
    Nodo(int id, float w, float h) : id(id), w(w), h(h), x(0), y(0), esHoja(false) {}
    int getId() const { return id; }
    float getWidth() const { return w; }
    float getHeight() const { return h; }
    void setId(int nuevoId) {
        id = nuevoId;
    }
    float getX() const { return x; }
    float getY() const { return y; }
    void setPosicion(float px, float py) {x = px; y = py;}
    void setEsHoja(bool hoja) {esHoja = hoja;}
    bool getEsHoja() const {return esHoja;}
    void setDimensiones(float width, float height) {w = width; h = height;}
    void imprimirNodo() const {
        cout << "Nodo ID: " << id
             << " | Ancho x Alto: " << w << "x" << h 
             << " | X, Y: (" << x << ", " << y << ")"
             << " | Es Hoja: " << (esHoja ? "Sí" : "No") << endl;
    }
};


#endif /* CLNODO_H */

