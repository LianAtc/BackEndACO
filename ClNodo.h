/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClNodo.h
 * Author: 20180954 Lian Abril Tume Cusi
 * Created on 22 de septiembre de 2024, 01:16 PM
 */

#ifndef CLNODO_H
#define CLNODO_H
#include <fstream>
using namespace std;

class Nodo {
public:
    int id;
    string valor;     // Puede ser un número de pieza o un operador ("H" o "V")
    Nodo* izquierda;  // Hijo izquierdo
    Nodo* derecha;    // Hijo derecho

    // Constructor de la clase Nodo
    Nodo(string v) : id(id),valor(v), izquierda(nullptr), derecha(nullptr) {}
    int getIdNodo() const {return id;}
};


#endif /* CLNODO_H */

