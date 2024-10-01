/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClGrafo.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 22 de septiembre de 2024, 01:23 PM
 */

#ifndef CLGRAFO_H
#define CLGRAFO_H
#include <fstream>
using namespace std;
#include "ClNodo.h"
#include "ClArista.h"

class Grafo {
private:
    vector<Nodo> nodos;
    vector<Arista> aristas;
    int proximoId;  // Nueva variable para controlar el ID de los nodos

public:
    Grafo() : proximoId(0) {}  // Inicializamos el ID en 0

    void agregarNodo(Nodo nodo) {
        nodo.setId(proximoId++);  // Asignamos el siguiente ID disponible al nodo y lo incrementamos
        nodos.push_back(nodo);
    }

    void agregarArista(Arista arista) {
        aristas.push_back(arista);
    }

    void inicializarFeromonas(float valorInicial) {
        for (auto& arista : aristas) {
            arista.setFeromonas(valorInicial);
        }
    }
    
    void actualizarFeromonas(float rho) {
        for (auto& arista : aristas) {
            float nuevaFeromona = arista.getFeromonas() * (1 - rho);
            arista.setFeromonas(nuevaFeromona);
        }
    }

    void actualizarNodo(Nodo nodo) {
        for (auto& n : nodos) {
            if (n.getId() == nodo.getId()) {
                n = nodo;
                break;
            }
        }
    }

    void imprimirGrafo() const {
        cout << "Nodos del grafo:" << endl;
        for (const auto& nodo : nodos) {
            nodo.imprimirNodo();
        }

        cout << "Aristas del grafo:" << endl;
        for (const auto& arista : aristas) {
            arista.imprimirArista();
        }
    }
    
    const vector<Nodo>& obtenerNodos() const {
        return nodos;
    }
};


#endif /* CLGRAFO_H */

