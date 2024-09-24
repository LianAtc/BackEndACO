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

class Grafo {
private:
    std::vector<Nodo> nodos;
    std::vector<Arista> aristas;

public:
    // Inicialización
    void agregarNodo(Nodo nodo) {
        nodos.push_back(nodo);
    }
    void agregarArista(Arista arista) {
        aristas.push_back(arista);
    }
    // Impresión
    void imprimirGrafo() const {
        std::cout << "Nodos en el Grafo:" << std::endl;
        for (const auto& nodo : nodos) {
            nodo.imprimirNodo();
        }
        std::cout << "Aristas en el Grafo:" << std::endl;
        for (const auto& arista : aristas) {
            arista.imprimirArista();
        }
    }
};

#endif /* CLGRAFO_H */

