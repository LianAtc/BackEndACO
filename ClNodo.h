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
    bool esHoja;

public:
    // Inicialización
    Nodo(int id, float w, float h, bool esHoja): id(id), w(w), h(h), esHoja(esHoja) {}
    // Obtener valores (privados)
    float getAncho() const { return w; }
    float getAlto() const { return h; }
    // Impresión
    void imprimirNodo() const {
        std::cout << "Nodo ID: " << id << ", Dimensiones: (" << w << ", " << h << "), Es hoja: " << (esHoja ? "Sí" : "No") << std::endl;
    }
};

#endif /* CLNODO_H */

