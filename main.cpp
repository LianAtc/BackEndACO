#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>

// Clase Pieza
class Pieza {
private:
    int id;
    float x, y;
    float w, h;
    bool r;

public:
    Pieza(int id, float x, float y, float w, float h, bool r)
        : id(id), x(x), y(y), w(w), h(h), r(r) {}

    void mostrar() const {
        std::cout << "Pieza ID: " << id << ", Posición: (" << x << ", " << y
                  << "), Dimensiones: (" << w << ", " << h << "), Rotada: " << (r ? "Sí" : "No") << std::endl;
    }
};

// Clase Base
class Base {
private:
    float W, H;
    std::vector<std::pair<float, float>> cortes;

public:
    Base(float W, float H) : W(W), H(H) {}

    void agregarCorte(float x, float y) {
        cortes.emplace_back(x, y);
    }

    void mostrarCortes() const {
        std::cout << "Cortes en la base (" << W << ", " << H << "):" << std::endl;
        for (const auto& corte : cortes) {
            std::cout << "Corte en: (" << corte.first << ", " << corte.second << ")" << std::endl;
        }
    }
};

// Clase Solucion
class Solucion {
private:
    std::list<Pieza> piezas;
    Base base;
    float desperdicio;

public:
    Solucion(Base base) : base(base), desperdicio(0) {}

    void agregarPieza(Pieza pieza) {
        piezas.push_back(pieza);
    }

    void mostrar() const {
        std::cout << "Solución:" << std::endl;
        for (const auto& pieza : piezas) {
            pieza.mostrar();
        }
        base.mostrarCortes();
        std::cout << "Desperdicio: " << desperdicio << std::endl;
    }
};

// Clase Nodo
class Nodo {
private:
    int id;
    float w, h;
    bool esHoja;

public:
    Nodo(int id, float w, float h, bool esHoja)
        : id(id), w(w), h(h), esHoja(esHoja) {}

    void mostrar() const {
        std::cout << "Nodo ID: " << id << ", Dimensiones: (" << w << ", " << h << "), Es hoja: " << (esHoja ? "Sí" : "No") << std::endl;
    }
};

// Clase Arista
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

    void mostrar() const {
        std::cout << "Arista entre Nodo ";
        nodoInicial.mostrar();
        std::cout << " y Nodo ";
        nodoFinal1.mostrar();
        std::cout << " o ";
        nodoFinal2.mostrar();
        std::cout << "Posición del corte: " << posicionCorte
                  << ", Tipo de corte: " << tipoCorte
                  << ", Desperdicio: " << desperdicio
                  << ", Feromonas: " << feromonas << std::endl;
    }
};

// Clase Hormiga
class Hormiga {
private:
    Solucion solucion;
    std::list<Pieza> piezasPendientes;

public:
    Hormiga(Solucion sol) : solucion(sol) {}

    void agregarPiezaPendiente(Pieza pieza) {
        piezasPendientes.push_back(pieza);
    }

    void mostrar() const {
        std::cout << "Hormiga - Solución: " << std::endl;
        solucion.mostrar();
        std::cout << "Piezas pendientes:" << std::endl;
        for (const auto& pieza : piezasPendientes) {
            pieza.mostrar();
        }
    }
};

// Clase Grafo
class Grafo {
private:
    std::vector<Nodo> nodos;
    std::vector<Arista> aristas;

public:
    void agregarNodo(Nodo nodo) {
        nodos.push_back(nodo);
    }

    void agregarArista(Arista arista) {
        aristas.push_back(arista);
    }

    void mostrar() const {
        std::cout << "Nodos en el Grafo:" << std::endl;
        for (const auto& nodo : nodos) {
            nodo.mostrar();
        }
        std::cout << "Aristas en el Grafo:" << std::endl;
        for (const auto& arista : aristas) {
            arista.mostrar();
        }
    }
};

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
    grafo.mostrar();

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
    hormiga.mostrar();

    return 0;
}
