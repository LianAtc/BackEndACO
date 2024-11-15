/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClBase.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 5 de septiembre de 2024, 10:55 PM
 */

#ifndef CLBASE_H
#define CLBASE_H
#include <fstream>
using namespace std;

class Stock {
private:
    float w, h;
    Nodo* arbol;
    list<Pieza> listaDefectos; // Solo contiene piezas defectuosas

public:
    Stock(int w, int h) : w(w), h(h), arbol(nullptr) {}
    Stock() : w(0), h(0), arbol(nullptr) {}

    void agregarPieza(const Pieza& pieza) {
        listaDefectos.push_back(pieza);
    }
    float getW() const { return w; }
    float getH() const { return h; }
    void setH(int nuevoAlto) {h = nuevoAlto;}
    void imprimirPiezas() const {
        cout << "Piezas en stock (" << w << "x" << h << "):\n";
        for (const Pieza& pieza : listaDefectos) {
            pieza.imprimirPieza();
        }
    }
    float calcularArea() const {return w * h;}

    void generarDefecto() {
        // Verifica si hay piezas en el stock
        if (!listaDefectos.empty()) {
            // Elegir un índice aleatorio
            int index = rand() % listaDefectos.size();
            auto it = listaDefectos.begin();
            advance(it, index);
            
            // Crear una nueva pieza defectuosa
            Pieza defecto(it->getID(), it->getX(), it->getY(), it->getW(), it->getH(), true);
            
            // Limpiar la lista de defectos y agregar la pieza defectuosa
            listaDefectos.clear(); // Asegurarte de que sea el único defecto
            listaDefectos.push_back(defecto);
        }
    }
    
    void imprimirStock() const { // Método para imprimir detalles del stock
        cout << "Stock de dimensiones: " << w << "x" << h << endl;
        //cout << "Total de piezas en stock: " << listaDefectos.size() << endl;
    }
};


#endif /* CLBASE_H */

