/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClACO.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 8 de septiembre de 2024, 10:53 AM
 */

#ifndef CLACO_H
#define CLACO_H
#include <fstream>
using namespace std;

class MatrizFeromonas {
private:
    list<list<double>> matriz;
}

class HistorialSoluciones {
private:
    list<Solucion> soluciones;
}

class Colonia {
private:
    vector<Hormiga> hormigas;
    MatrizFeromonas feromonas;
    int numIteraciones;
    double tasaEvaporacion;
};

class Hormiga {
    Solucion solucion;
}


#endif /* CLACO_H */

