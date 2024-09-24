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
    Nodo nodoFinal1;
    Nodo nodoFinal2;
    float posicionCorte;
    std::string tipoCorte;
    float desperdicio;
    float feromonas;

public:
    Arista(Nodo inicio, Nodo final1, Nodo final2, float posicionCorte, std::string tipoCorte, float desperdicio, float feromonas)
        : nodoInicial(inicio), nodoFinal1(final1), nodoFinal2(final2), posicionCorte(posicionCorte), tipoCorte(tipoCorte), desperdicio(desperdicio), feromonas(feromonas) {}
    float getFeromonas() const { return feromonas; }
    void setFeromonas(float newValue) { feromonas = newValue; }    
    void imprimirArista() const {
        std::cout << "Arista entre Nodo ";
        nodoInicial.imprimirNodo();
        std::cout << " y Nodo ";
        nodoFinal1.imprimirNodo();
        std::cout << " o ";
        nodoFinal2.imprimirNodo();
        std::cout << "Posición del corte: " << posicionCorte
                  << ", Tipo de corte: " << tipoCorte
                  << ", Desperdicio: " << desperdicio
                  << ", Feromonas: " << feromonas << std::endl;
    }
};

#endif /* CLARISTA_H */

