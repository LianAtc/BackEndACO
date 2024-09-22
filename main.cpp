#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>

#include "ClPieza.h"
#include "ClBase.h"

#include "ClSolucion.h"

#include "ClNodo.h"
#include "ClArista.h"
#include "ClGrafo.h"

#include "ClHormiga.h"

int main() {
    // Crear nodos
    Nodo nodo1(1, 10.0f, 20.0f, true);
    Nodo nodo2(2, 15.0f, 25.0f, false);
    Nodo nodo3(3, 20.0f, 30.0f, true);

    // Crear arista
    Arista arista(nodo1, nodo2, nodo3, 5.0f, "Vertical", 2.0f, 0.5f);

    // Crear grafo
    Grafo grafo;
    grafo.agregarNodo(nodo1);
    grafo.agregarNodo(nodo2);
    grafo.agregarNodo(nodo3);
    grafo.agregarArista(arista);

    // Mostrar el grafo
    grafo.imprimirGrafo();

    // Crear una base
    Base base(100.0f, 50.0);
    base.agregarCorte(10.0, 20.0);
    base.agregarCorte(30.0, 40.0);

    // Crear una solución
    Solucion solucion(base);
    solucion.agregarPieza(Pieza(1, 5.0, 5.0, 10.0, 15.0, false));
    solucion.agregarPieza(Pieza(2, 15.0, 10.0, 20.0, 5.0, true));

    // Crear una hormiga
    Hormiga hormiga(solucion);
    hormiga.agregarPiezaPendiente(Pieza(3, 8.0, 8.0, 12.0, 18.0, false));

    // Mostrar la hormiga
    hormiga.imprimirHormiga();

    return 0;
}
