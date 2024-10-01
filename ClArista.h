/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClArista.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 22 de septiembre de 2024, 01:18 PM
 */

#ifndef CLARISTA_H
#define CLARISTA_H
#include <fstream>
using namespace std;

class Arista {
private:
    Nodo nodoInicial;
    Nodo nodoFinal1, nodoFinal2;
    float posicionCorte;
    string tipoCorte;
    float desperdicio;
    float feromonas;
public:
    Arista(Nodo ni, Nodo nf1, Nodo nf2, float posCorte, string tipo, float f) 
        : nodoInicial(ni), nodoFinal1(nf1), nodoFinal2(nf2), posicionCorte(posCorte), tipoCorte(tipo), feromonas(f) {}
    float getFeromonas() const { return feromonas; }
    void setFeromonas(float valor) { feromonas = valor; }
    void actualizarFeromonas(float delta) { feromonas += delta; }
    Nodo getNodoFinal1() const { return nodoFinal1; }
    Nodo getNodoFinal2() const { return nodoFinal2; }
    string getTipoCorte() const { return tipoCorte; }
    float getPosicionCorte() const {return posicionCorte;}
    void imprimirArista() const {
        cout << "Arista entre nodos:" << endl;
        cout << "Nodo Inicial: ";
        nodoInicial.imprimirNodo();
        cout << "Nodo Final 1: ";
        nodoFinal1.imprimirNodo();
        cout << "Nodo Final 2: ";
        nodoFinal2.imprimirNodo();
        cout << "Posición de Corte: " << posicionCorte << endl;
        cout << "Tipo de Corte: " << tipoCorte << endl;
        cout << "Feromonas: " << feromonas << endl;
    }
};

#endif /* CLARISTA_H */

