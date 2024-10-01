#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <cstdlib>   // for srand, rand
#include <ctime>     // for time
#include <algorithm>
#include <tuple>
#include <queue>
#include <set>

#include "ClBase.h"
#include "ClPieza.h"

#include "ClHormiga.h"

#include "ClNodo.h"
#include "ClArista.h"

using namespace std;

class Espacio {
private:
    vector<tuple<float, float, float, float>> espaciosLibres;
public:
    Espacio(float anchoBase, float altoBase) {
        espaciosLibres.push_back(make_tuple(0, 0, anchoBase, altoBase));
    }
    bool hayEspacio(float anchoPieza, float altoPieza, float& xPos, float& yPos) {
        for (auto& espacio : espaciosLibres) {
            float x = get<0>(espacio);
            float y = get<1>(espacio);
            float w = get<2>(espacio);
            float h = get<3>(espacio);
            if (w >= anchoPieza && h >= altoPieza) {
                xPos = x;
                yPos = y;
                actualizarEspacios(x, y, anchoPieza, altoPieza);
                return true;
            }
        }
        return false;
    }
    void actualizarEspacios(float xPos, float yPos, float anchoPieza, float altoPieza) {
        vector<tuple<float, float, float, float>> nuevosEspacios;
        for (auto& espacio : espaciosLibres) {
            float x = get<0>(espacio);
            float y = get<1>(espacio);
            float w = get<2>(espacio);
            float h = get<3>(espacio);
            if (x == xPos && y == yPos) {
                if (w > anchoPieza) {
                    nuevosEspacios.push_back(make_tuple(xPos + anchoPieza, yPos, w - anchoPieza, altoPieza));
                }
                if (h > altoPieza) {
                    nuevosEspacios.push_back(make_tuple(xPos, yPos + altoPieza, anchoPieza, h - altoPieza));
                }
                if (w > anchoPieza && h > altoPieza) {
                    nuevosEspacios.push_back(make_tuple(xPos + anchoPieza, yPos + altoPieza, w - anchoPieza, h - altoPieza));
                }
            } else {
                nuevosEspacios.push_back(espacio);
            }
        }
        espaciosLibres = nuevosEspacios;
    }

    void imprimirEspaciosLibres() const {
        cout << "Espacios libres actuales:\n";
        for (const auto& espacio : espaciosLibres) {
            cout << "Posición: (" << get<0>(espacio) << ", " << get<1>(espacio) 
                      << "), Dimensiones: (" << get<2>(espacio) << "x" << get<3>(espacio) << ")\n";
        }
    }
};

float calcularDesperdicio(const Base& base, const list<Pieza>& piezasCortadas) {
    float areaCortada = 0.0;
    for (const Pieza& p : piezasCortadas) {
        areaCortada += p.getWidth() * p.getHeight();
    }
    float areaBase = base.getWidth() * base.getHeight();
    return areaBase - areaCortada;
}

void imprimirCola(queue<Nodo> nodosPorCortar) {
    while (!nodosPorCortar.empty()) {
        Nodo nodoActual = nodosPorCortar.front();
        nodoActual.imprimirNodo();
        nodosPorCortar.pop();
    }
}

float CalcularHeuristica(Nodo& nodoActual, const std::list<Pieza>& piezasRestantes) {
    float areaNodo = nodoActual.getWidth() * nodoActual.getHeight();
    float menorDesperdicio = areaNodo;
    Pieza* mejorPieza = nullptr;
    bool rotacion = false;

    for (const Pieza& pieza : piezasRestantes) {
        float areaPieza = pieza.getWidth() * pieza.getHeight();
        bool encajaSinRotar = (pieza.getWidth() <= nodoActual.getWidth() && pieza.getHeight() <= nodoActual.getHeight());
        bool encajaRotada = (pieza.getHeight() <= nodoActual.getWidth() && pieza.getWidth() <= nodoActual.getHeight());

        if (encajaSinRotar) {
            float desperdicio = areaNodo - areaPieza; 
            if (desperdicio < menorDesperdicio) {
                menorDesperdicio = desperdicio;
                mejorPieza = const_cast<Pieza*>(&pieza);
                rotacion = false;
            }
        }
        if (encajaRotada) {
            float desperdicio = areaNodo - areaPieza;
            if (desperdicio < menorDesperdicio) {
                menorDesperdicio = desperdicio;
                mejorPieza = const_cast<Pieza*>(&pieza);
                rotacion = true;
            }
        }
    }
    if (mejorPieza != nullptr) {
        if (rotacion) {
            mejorPieza->rotarPieza();
        }
        nodoActual.setEsHoja(true);
    }
    return menorDesperdicio;
}

Hormiga ConstSol(Grafo& grafo, Nodo& nodoActual, list<Pieza>& piezasRestantes, float alpha, float beta, Base& base, Espacio& espacioLibre) {
    Hormiga sol(base);
    queue<Nodo> nodosPorCortar;
    nodosPorCortar.push(nodoActual);
    float desperdicioTotal = 0;

    while (!piezasRestantes.empty() && !nodosPorCortar.empty()) {
        nodoActual = nodosPorCortar.front();
        nodosPorCortar.pop();

        bool nodoMuyPequeno = true;
        for (const auto& pieza : piezasRestantes) {
            if ((nodoActual.getWidth() >= pieza.getWidth() && nodoActual.getHeight() >= pieza.getHeight()) ||
                (nodoActual.getWidth() >= pieza.getHeight() && nodoActual.getHeight() >= pieza.getWidth())) {
                nodoMuyPequeno = false; 
                break;
            }
        }

        if (nodoMuyPequeno) {
            float areaNodo = nodoActual.getWidth() * nodoActual.getHeight();
            desperdicioTotal += areaNodo;
            continue;
        }

        bool subpiezaEsHoja = false;
        auto it = piezasRestantes.begin();
        while (it != piezasRestantes.end()) {
            float xPos, yPos;
            bool piezaRotada = false;

            if (nodoActual.getWidth() == it->getWidth() && nodoActual.getHeight() == it->getHeight()) {
                piezaRotada = false;
            } 
            else if (nodoActual.getWidth() == it->getHeight() && nodoActual.getHeight() == it->getWidth()) {
                piezaRotada = true;
                it->rotarPieza();
            }
            if ((nodoActual.getWidth() == it->getWidth() && nodoActual.getHeight() == it->getHeight()) ||
                (nodoActual.getWidth() == it->getHeight() && nodoActual.getHeight() == it->getWidth())) {
                
                if (espacioLibre.hayEspacio(it->getWidth(), it->getHeight(), xPos, yPos)) {
                    it->setPosicion(xPos, yPos);
                    sol.agregarPieza(*it);
                    nodoActual.setEsHoja(true);
                    grafo.actualizarNodo(nodoActual);
                    it = piezasRestantes.erase(it);
                    subpiezaEsHoja = true;
                    break;
                }
            }
            ++it;
        }
        if (!subpiezaEsHoja) {
            Nodo subpieza1(nodoActual.getId() + 1, nodoActual.getWidth() / 2, nodoActual.getHeight());
            Nodo subpieza2(nodoActual.getId() + 2, nodoActual.getWidth() - subpieza1.getWidth(), nodoActual.getHeight());
            
            grafo.agregarNodo(subpieza1);
            grafo.agregarNodo(subpieza2);
            grafo.agregarArista(Arista(nodoActual, subpieza1, subpieza2, nodoActual.getWidth() / 2, "vertical", 0.1f));  // Definir la arista para el corte
            
            nodosPorCortar.push(subpieza1);
            nodosPorCortar.push(subpieza2);
        }
    }
    desperdicioTotal += calcularDesperdicio(sol.getBase(), sol.getPiezas());
    sol.setDesperdicio(desperdicioTotal);
    cout << "Desperdicio total: " << desperdicioTotal << endl;

    cout << "Grafo de esta solucion: " << endl;
    grafo.imprimirGrafo();
    return sol;
}

bool nodosPequenos(const Grafo& grafo, const vector<Pieza>& piezas) {
    list<Pieza> piezasRestantes(piezas.begin(), piezas.end());

    for (const auto& nodo : grafo.obtenerNodos()) {
        for (const auto& pieza : piezasRestantes) {
            if (nodo.getWidth() >= pieza.getWidth() && nodo.getHeight() >= pieza.getHeight()) {
                return false;
            }
        }
    }
    return true;
}

void AlgoritmoACO(Base& base, vector<Pieza>& piezas, int nHormigas, int maxIter, float alpha, float beta, float rho, int tol) {
    Grafo grafo;
    Nodo nodoInicial(0, base.getWidth(), base.getHeight());
    grafo.agregarNodo(nodoInicial);
    grafo.inicializarFeromonas(0.1);
    Espacio espacioLibre(base.getWidth(), base.getHeight());
    Hormiga mejorSol(base);
    int sinMej = 0;
    cout << "Iniciando algoritmo ACO..." << endl;
    
    for (int iter = 0; iter < maxIter && sinMej < tol; ++iter) {
        vector<Hormiga> soluciones;
        for (int h = 0; h < nHormigas; ++h) {
            list<Pieza> piezasRestantes(piezas.begin(), piezas.end());
            Hormiga sol = ConstSol(grafo, nodoInicial, piezasRestantes, alpha, beta, base, espacioLibre);
            soluciones.push_back(sol);
            if (nodosPequenos(grafo, piezas)) {
                break;
            }
        }
        Hormiga mejorIter = *min_element(soluciones.begin(), soluciones.end(), [](const Hormiga& a, const Hormiga& b) {
            return a.getDesperdicio() < b.getDesperdicio();
        });
        
        if (mejorIter.getDesperdicio() < mejorSol.getDesperdicio()) {
            mejorSol = mejorIter;
            mejorIter.imprimirSolucion();
            sinMej = 0;
        } else {
            sinMej++;
        }

        grafo.actualizarFeromonas(rho);
        if(iter == 0) mejorSol = mejorIter;
    }
    cout << "Imprimiendo mejor solución..." << endl;
    mejorSol.imprimirSolucion();
    cout << "Imprimiendo Grafo" << endl;
    grafo.imprimirGrafo();
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    Base base(200, 200);
    Espacio espacioLibre(base.getWidth(), base.getHeight());
    
    vector<Pieza> piezas = { 
        Pieza(1, 50, 200),
        Pieza(2, 50, 200),
        Pieza(3, 200, 50), 
        Pieza(4, 200, 50),
        Pieza(5, 50, 50),
        Pieza(6, 40, 40),
        Pieza(7, 30, 30),
        Pieza(8, 60, 60),
        Pieza(9, 80, 80),
        Pieza(10, 90, 45),
        Pieza(11, 20, 20),
        Pieza(12, 70, 50),
        Pieza(13, 35, 35),
        Pieza(14, 45, 15),
        Pieza(15, 85, 85)
    };


    int nHormigas = 1;
    int maxIter = 1;
    float alpha = 1.0, beta = 2.0, rho = 0.1;
    int tol = 1;

    cout << "Iniciando algoritmo ACO con " << nHormigas << " hormigas..." << endl;
    AlgoritmoACO(base, piezas, nHormigas, maxIter, alpha, beta, rho, tol);
    cout << "Ejecución del algoritmo ACO finalizada." << endl;
    
    return 0;
}
