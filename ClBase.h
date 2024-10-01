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

class Base {
private:
    float W, H; 
    vector<pair<float, float>> cortes;
public:
    Base(float W, float H) : W(W), H(H) {}
    float area() const { return W * H; }
    void agregarCorte(float x, float y) {
        cortes.push_back(make_pair(x, y));
    }
    vector<pair<float, float>> getCortes() const {
        return cortes;
    }
    float getWidth() const { return W; }
    float getHeight() const { return H; }
};


#endif /* CLBASE_H */

