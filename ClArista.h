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
    int idArista;
    int nodoInicial,nodoFinal;
    string tipoCorte;
    float feromonas; 
    float heuristica;

public:
    Arista(int idArista, int nodoInicial, int nodoFinal, const string& tipoCorte, float feromonas, float heuristica)
        : idArista(idArista), nodoInicial(nodoInicial), nodoFinal(nodoFinal), tipoCorte(tipoCorte), feromonas(feromonas), heuristica(heuristica) {}
    int getID() const { return idArista; }
    int getNodoInicial() const { return nodoInicial; }
    int getNodoFinal() const { return nodoFinal; }
    string getTipoCorte() const { return tipoCorte; } 
    float getFeromonas() const { return feromonas; }
    float getHeuristica() const { return heuristica; }
    void setFeromonas(float valor) {feromonas = valor;}
    void agregarFeromonas(float delta) { feromonas += delta; }
    //void evaporarFeromonas(float rho) { feromonas *= (1.0 - rho); }
};


#endif /* CLARISTA_H */

