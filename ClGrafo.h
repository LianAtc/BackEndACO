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
    vector<Nodo*> nodos;
    vector<Arista*> aristas;
    set<pair<int, int>> conexiones; // Para almacenar pares de nodos conectados

public:
    Grafo() {}

    void agregarNodo(Nodo* nodo) {
        nodos.push_back(nodo);
    }

    void agregarArista(Arista* arista) {
        aristas.push_back(arista);
        // Conexión bidireccional
        conexiones.insert({arista->getNodoInicial(), arista->getNodoFinal()});
        conexiones.insert({arista->getNodoFinal(), arista->getNodoInicial()});
    }

    bool existeConexion(int nodo1, int nodo2) {
        return conexiones.find({nodo1, nodo2}) != conexiones.end();
    }

    // Generar un grafo completo donde cada nodo está conectado a todos los demás
    void generarGrafoCompleto() {
        for (int i = 0; i < nodos.size(); ++i) {
            for (int j = i + 1; j < nodos.size(); ++j) {
                if (!existeConexion(nodos[i]->getIdNodo(), nodos[j]->getIdNodo())) {
                    string tipoCorte = (rand() % 2 == 0) ? "H" : "V";
                    Arista* arista = new Arista(aristas.size(), nodos[i]->getIdNodo(), nodos[j]->getIdNodo(), tipoCorte, 1.0, 1.0);
                    agregarArista(arista);
                }
            }
        }
    }
    
    float obtenerFeromonas(int idNodo1, int idNodo2) {
        for (Arista* arista : aristas) {
            if ((arista->getNodoInicial() == idNodo1 && arista->getNodoFinal() == idNodo2) ||
                (arista->getNodoInicial() == idNodo2 && arista->getNodoFinal() == idNodo1)) {
                
                // Retorna el valor de las feromonas si la arista conecta los dos nodos
                return arista->getFeromonas();
            }
        }
        // Si no encuentra la arista, retorna -1 como señal de que no existe la arista
        return -1.0;
    }
    
    bool aumentarFeromonas(int idNodo1, int idNodo2, float incremento) {
        for (Arista* arista : aristas) {
            if ((arista->getNodoInicial() == idNodo1 && arista->getNodoFinal() == idNodo2) ||
                (arista->getNodoInicial() == idNodo2 && arista->getNodoFinal() == idNodo1)) {
                
                // Aumentar el valor de las feromonas
                float nuevasFeromonas = arista->getFeromonas() + incremento;
                arista->setFeromonas(nuevasFeromonas);
                return true;  // Encontró y actualizó la arista
            }
        }
        return false;  // No encontró una arista que conecte los dos nodos
    }
    
    void evaporarFeromonas(float rho) {
        for (Arista* arista : aristas) {
            float feromonasActuales = arista->getFeromonas();
            float nuevasFeromonas = feromonasActuales * (1 - rho);
            arista->setFeromonas(nuevasFeromonas);
        }
    }
    
    void inicializarFeromonas(float valor) {
        for (Arista* arista : aristas) {
            arista->setFeromonas(valor);
        }
    }

    void imprimirConexionesCompacto() const {
        for (const Nodo* nodo : nodos) {
            cout << "Nodo " << nodo->getIdNodo() << " -> [";
            bool primero = true;
            for (const Arista* arista : aristas) {
                if (arista->getNodoInicial() == nodo->getIdNodo()) {
                    if (!primero) cout << ", ";
                    cout << arista->getNodoFinal();
                    primero = false;
                } else if (arista->getNodoFinal() == nodo->getIdNodo()) {
                    if (!primero) cout << ", ";
                    cout << arista->getNodoInicial();
                    primero = false;
                }
            }
            cout << "]" << endl;
        }
    }
};


#endif /* CLGRAFO_H */

