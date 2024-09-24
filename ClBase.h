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

#include "ClPieza.h"

class Base {
private:
    float W, H;
    std::vector<std::pair<float, float>> cortes;
public:
    // Inicialización
    Base(float W, float H) : W(W), H(H) {}
    void agregarCorte(float x, float y) {
        cortes.emplace_back(x, y);
    }
    // Extras
    float area() const { return W * H; }
    // Impresión
    void imprimirCortes() const {
        std::cout << "Cortes en la base (" << W << ", " << H << "):" << std::endl;
        for (const auto& corte : cortes) {
            std::cout << "Corte en: (" << corte.first << ", " << corte.second << ")" << std::endl;
        }
    }
};

#endif /* CLBASE_H */

