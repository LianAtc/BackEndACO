#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stack>
#include <set>
#include <cmath>

#include "ClArista.h"
#include "ClNodo.h"
#include "ClGrafo.h"

#include "ClPieza.h"
#include "ClBase.h"

#define MAX 70

using namespace std;

int numPiezas = 90;
vector<Pieza> listaPiezasResultante;
vector<Pieza> solucion;
float anchoMayor,altoMayor;
double desTotal;


vector<Pieza> generarListaPiezas(int cantidad) {
    vector<Pieza> listaPiezas;
    vector<pair<float, float>> medidasDisponibles = {
        {45, 8.6}, {15, 7.5}, 
        {40, 25.0}, {40, 8.0},
        {40, 20.0}, {30, 15.0},
        {20, 10.0}, {40, 10.0},
        {30, 7.5}, {25, 12.0},
        {50, 9.5}, {35, 8.0},
        {60, 10.0}, {45, 12.5},
        {25, 5.0}, {55, 15.0},
        {65, 20.0}, {20, 7.0},
        {30, 5.5}, {40, 6.5},
        {50, 12.0}, {35, 10.0},
        {25, 8.0}, {45, 10.5},
        {55, 11.5}, {30, 20.0},
        {60, 15.0}, {35, 7.5},
        {20, 5.0}, {25, 10.0},
        {45, 8.6}, {15, 7.5}, 
        {40, 25.0}, {40, 8.0},
        {40, 20.0}, {30, 15.0},
        {20, 10.0}, {40, 10.0},
        {30, 7.5}, {25, 12.0},
        {50, 9.5}, {35, 8.0},
        {60, 10.0}, {45, 12.5},
        {25, 5.0}, {55, 15.0},
        {65, 20.0}, {20, 7.0},
        {30, 5.5}, {40, 6.5},
        {50, 12.0}, {35, 10.0},
        {25, 8.0}, {45, 10.5},
        {55, 11.5}, {30, 20.0},
        {60, 15.0}, {35, 7.5},
        {20, 5.0}, {25, 10.0},
        {45, 8.6}, {15, 7.5}, 
        {40, 25.0}, {40, 8.0},
        {40, 20.0}, {30, 15.0},
        {20, 10.0}, {40, 10.0},
        {30, 7.5}, {25, 12.0},
        {50, 9.5}, {35, 8.0},
        {60, 10.0}, {45, 12.5},
        {25, 5.0}, {55, 15.0},
        {65, 20.0}, {20, 7.0},
        {30, 5.5}, {40, 6.5},
        {50, 12.0}, {35, 10.0},
        {25, 8.0}, {45, 10.5},
        {55, 11.5}, {30, 20.0},
        {60, 15.0}, {35, 7.5},
        {20, 5.0}, {25, 10.0}
    };

    for (int i = 0; i < cantidad; ++i) {
        float x = 0;
        float y = 0;
        bool rotada = 0;

        int indiceAleatorio = rand() % medidasDisponibles.size();
        float w = medidasDisponibles[i].first;
        float h = medidasDisponibles[i].second;
        
        Pieza p(i, x, y, w, h, rotada);
        listaPiezas.push_back(p);
    }
    return listaPiezas;
}

vector<Stock> generarListaStocks(int cantidad) {
    vector<Stock> listaStocks;
    
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < cantidad; ++i) {
        int w, h;
        
        if (rand() % 2 == 0) {
            w = 60;
            h = 60;
        } else {
            w = 60;
            h = 60;
        }
        
        Stock s(w, h); 
        listaStocks.push_back(s);
    }
    
    return listaStocks;
}

bool compararPiezas(const Pieza& a, const Pieza& b) {
    return (a.getH() >b.getH());
}

void ordenarPiezas(vector<Pieza>& listaPiezas) {
    sort(listaPiezas.begin(), listaPiezas.end(), compararPiezas);
}

bool compararStocks(const Stock& a, const Stock& b) {
    return (a.getW() * a.getH()) > (b.getW() * b.getH());
}

void ordenarStocks(vector<Stock>& stocks) {
    sort(stocks.begin(), stocks.end(), compararStocks);
}

const Pieza* buscarPiezaPorId(int id, const vector<Pieza>& listaPiezas) {
    for (const auto& pieza : listaPiezas) {
        if (pieza.getID() == id) {
            return &pieza; // Devolver la pieza si se encuentra
        }
    }
    return nullptr; // Si no se encuentra, devolver nullptr
}


vector<Pieza> crearListaPiezas(const std::vector<int>& indicePiezaEscogida, const std::vector<Pieza>& listaPiezas) {
    vector<Pieza> listaPiezasResultante;

    for (int id : indicePiezaEscogida) {
        const Pieza* pieza = buscarPiezaPorId(id, listaPiezas);
        if (pieza != nullptr) {
            listaPiezasResultante.push_back(*pieza); // Añade la pieza encontrada a la lista resultante
        } else {
            std::cerr << "Advertencia: Pieza con ID " << id << " no encontrada." << std::endl;
        }
    }

    return listaPiezasResultante;
}

double calcularHeuristica(Stock& stock, Pieza& pieza) {
    double desperdicio, areaUsada, areaPiezas;
    double desperdicioOriginal = 1;
    double desperdicioRotado = 1;

    if (pieza.getH() <= stock.getH() && anchoMayor + pieza.getW() <= stock.getW()) {
        areaUsada = (altoMayor > pieza.getH()) ? 
            (altoMayor * (anchoMayor + pieza.getW())) : 
            (pieza.getH() * (anchoMayor + pieza.getW()));

        areaPiezas = (anchoMayor * altoMayor) + (pieza.getW() * pieza.getH());
        desperdicioOriginal = (areaUsada - areaPiezas) / areaUsada;
    }
    
    return desperdicioOriginal;
    pieza.rotarPieza();
    if (pieza.getH() <= stock.getH() && anchoMayor + pieza.getW() <= stock.getW()) {
        areaUsada = (altoMayor > pieza.getH()) ? 
            (altoMayor * (anchoMayor + pieza.getW())) : 
            (pieza.getH() * (anchoMayor + pieza.getW()));

        areaPiezas = (anchoMayor * altoMayor) + (pieza.getW() * pieza.getH());
        desperdicioRotado = (areaUsada - areaPiezas) / areaUsada;
    }

    if (desperdicioRotado < desperdicioOriginal) {
        if (desperdicioRotado == 0) return 0;    
        return desperdicioRotado;
    } else {
        pieza.rotarPieza();
        return desperdicioOriginal;
    }
}

double calcularDesperdicio(const std::vector<Pieza>& listaPiezas, const Stock& stock) {
    double areaTotalPiezas = 0;

    // Calcular el área total de las piezas directamente
    for (const auto& pieza : listaPiezas) {
        areaTotalPiezas += pieza.calcularArea();
    }

    double areaStock = stock.calcularArea();
    double desperdicio = areaTotalPiezas / areaStock; // Desperdicio en términos de proporción
    double fitness = (1.0 - desperdicio); // Fitness opcional si lo necesitas

    return fitness;
}

void ConstSol(float Q,float alpha, float beta, float rho, int tol, vector<Pieza>& listaPiezas2, vector<Stock>& listaStocks2, Grafo grafo) {
    Stock solucion;
    int numPiezaLista=0,indiceAleatorio=0,entra=0,a,b;
    float ancho,alto,menorH=100;
    int piezaEscogida,i=0,j=0,piezaPasada,intentos=0,indice;
    double feromonas,heuristica,probabilidad=100,mProb=0,incrementoFeromona;
    double epsilon = 1e-6, difHeu;
    vector<int> indicePiezaEscogida;
    
    vector<Pieza> listaPiezas = listaPiezas2;
    vector<Stock> listaStocks = listaStocks2;
    
    for (const Pieza& pieza2 : listaPiezas) {
        if (listaPiezas.empty()) break;
        entra=0;
        while(entra==0 && intentos < (numPiezas-1)){
            indiceAleatorio = rand() % (numPiezas-1); // Random por numero de piezas
            // Obtenemos el indice del id que queremos
            auto it = find_if(listaPiezas.begin(), listaPiezas.end(), 
                          [indiceAleatorio](const Pieza& pieza) {
                              return pieza.getID() == indiceAleatorio;
                          });

            if (it != listaPiezas.end()) {
                indice = distance(listaPiezas.begin(), it);
//                listaPiezas[indice].imprimirPieza();
            }
            
            if (find(indicePiezaEscogida.begin(), indicePiezaEscogida.end(), indiceAleatorio) == indicePiezaEscogida.end()) {
                if (listaPiezas[indice].getW() <= listaStocks[0].getW() && listaPiezas[indice].getH() <= listaStocks[0].getH()) {
                    entra=1;
                    indicePiezaEscogida.push_back(indiceAleatorio);
                }else{
                    entra=0;
                }
            }
            intentos++;
        }
        if(entra==0) break;
        intentos=0;
        // Impresión de nodo elegido
//        for(int i=0; i<100;i++) cout<<"=";
//        cout<<endl;
//        cout<< "Pieza Aleatoria:" <<endl;
//        cout<< "Indice : "<< indiceAleatorio <<endl;
//                  
        // Defino la longitud más grande a cortar en guillotina
        anchoMayor = listaPiezas[indice].getW();
        altoMayor = listaPiezas[indice].getH();
        
//        cout << "Ancho x Alto:" << anchoMayor << " , " << altoMayor<<endl;
//        for(int i=0; i<100;i++) cout<<"=";
//        cout<<endl;

        // Elimino pieza inicial
        auto it2 = std::find_if(listaPiezas.begin(), listaPiezas.end(), [indiceAleatorio](const Pieza& pieza) {
            return pieza.getID() == indiceAleatorio;
        });
        if (it2 != listaPiezas.end()) {
            listaPiezas.erase(it2);
        }
        i++;
        piezaPasada = indiceAleatorio;
        mProb = 0,heuristica=1,difHeu=1;
        for (const Pieza& pieza2 : listaPiezas) { //Encajo pieza
//            for(int i=0; i<100;i++) cout<<"=";
//            cout<<endl;
            difHeu=1;
            for (Pieza& pieza : listaPiezas) { // Escoger una pieza
                feromonas= grafo.obtenerFeromonas(indiceAleatorio,pieza.getID());
                heuristica = calcularHeuristica(listaStocks[0],pieza);
//                cout << "Heuristica: " <<heuristica<<endl;
                if (heuristica == 0) {
                    probabilidad = pow(feromonas, alpha) * pow(1 / epsilon, beta);
                } else {
                    probabilidad = pow(feromonas, alpha) * pow(1 / heuristica, beta);
                }
                if(mProb <= probabilidad){    
                    mProb = probabilidad;
                    piezaEscogida = pieza.getID();
                    alto = pieza.getH();
                    ancho = pieza.getW();
                }
                if(heuristica!=1)difHeu=heuristica;
//                pieza.imprimirPieza();
//                cout << "Probabilidad: " <<probabilidad<<endl;
            }
            if (difHeu == 1) break;

//            cout<< "Pieza Encajada: "<< piezaEscogida<< " ("<<alto<<"x"<<ancho<<")" <<endl;
            
            i++;

            if(altoMayor>alto){
                anchoMayor += ancho;
            }else{
                anchoMayor += ancho;
                altoMayor = alto;
            }
            
//            cout<< "Espacio: " << altoMayor << " , " << anchoMayor<<endl;
//            cout<< "Ancho y Alto Mayor: " << anchoMayor << " , "<<altoMayor<<endl;

            indicePiezaEscogida.push_back(piezaEscogida);
            piezaPasada = piezaEscogida;
            
            // Elimino pieza escogida
            auto it = std::find_if(listaPiezas.begin(), listaPiezas.end(), [piezaEscogida](const Pieza& pieza) {
                return pieza.getID() == piezaEscogida;
            });
            if (it != listaPiezas.end()) {
                listaPiezas.erase(it);
            }
            
            mProb=0;piezaEscogida=-1;
        }
//        for(int i=0; i<100;i++) cout<<"=";
//        cout<<endl;
//        cout<<"Cambio de nivel"<<endl;
        i=0;
        listaStocks[0].setH(listaStocks[0].getH()-altoMayor); // Actualizo el  nuevo alto
//        for(int i=0; i<100;i++) cout<<"=";
//        cout<<endl;
        altoMayor=0;
        anchoMayor=0;
        j++;
    }
    listaPiezasResultante = crearListaPiezas(indicePiezaEscogida,listaPiezas2);
    desTotal = calcularDesperdicio(listaPiezasResultante,listaStocks2[0]);
    incrementoFeromona = Q / (1.0 + desTotal);
    for (size_t k = 0; k < indicePiezaEscogida.size() - 1; ++k) {
        grafo.aumentarFeromonas(indicePiezaEscogida[k], indicePiezaEscogida[k + 1], incrementoFeromona);
    }
}

void colocarPiezasEnOrden(const std::vector<Pieza>& listaPiezas, Stock& stock) {
    float anchoMaximo = stock.getW();
    float altoMaximo = stock.getH();
    float anchoFilaActual = 0;
    float alturaFilaActual = 0;
    float alturaTotal = 0;

    std::cout << "Acomodando las piezas en el stock (" << anchoMaximo << "x" << altoMaximo << "):" << std::endl;

    for (const auto& pieza : listaPiezas) {
        // Verificar si la pieza cabe en la fila actual
        if (anchoFilaActual + pieza.getW() <= anchoMaximo) {
            // Colocar la pieza en la fila actual y actualizar la posición
            std::cout << "Pieza ID: " << pieza.getID() << " colocada en (" << anchoFilaActual << ", " << alturaTotal 
                      << "), Tamaño: " << pieza.getW() << "x" << pieza.getH() << std::endl;

            anchoFilaActual += pieza.getW();
            alturaFilaActual = std::max(alturaFilaActual, pieza.getH());
        } else {
            // Mover a la siguiente fila
            alturaTotal += alturaFilaActual;
            if (alturaTotal + pieza.getH() > altoMaximo) {
                std::cout << "La pieza ID: " << pieza.getID() << " no cabe en el stock restante. Colocación terminada." << std::endl;
                return; // Terminar la colocación si no hay más espacio en el stock
            }

            // Colocar la pieza en la nueva fila
            std::cout << "Pieza ID: " << pieza.getID() << " colocada en (0, " << alturaTotal 
                      << "), Tamaño: " << pieza.getW() << "x" << pieza.getH() << std::endl;

            anchoFilaActual = pieza.getW();
            alturaFilaActual = pieza.getH();
        }
    }

    std::cout << "Acomodación de piezas completada." << std::endl;
}

void imprimirSeparacion(int n){
    cout<<endl;
    for (int i=0;i <= n;i++) cout<<"=";
    cout<<endl;
}

void AlgoritmoACO(int nHormigas, int maxIter, float Q, float alpha, float beta, float rho, int tol, vector<Pieza>& listaPiezas, vector<Stock>& listaStocks, Grafo grafo) {
    Stock Solucion,mejorSolucion;
    int sinMej = 0,i=0,j=0; // Actualizar a 100
    double mejorDespTotal=100000, mejorDesp=100000;
    double desperdicio;
    //Inicializo feromonas
    grafo.inicializarFeromonas(rho);
    
    for (int iter = 0; iter < maxIter && sinMej < tol; ++iter) {
//        cout << "Iteracion " << iter+1 << endl;
        for (int h = 0; h < nHormigas; ++h) {
//            cout << "Iniciando algoritmo ACO con " << h+1 << " hormigas..." << endl;
            ConstSol(Q,alpha,beta,rho,tol,listaPiezas,listaStocks,grafo);
            if(desTotal<0.0) break;
            if (mejorDesp>desTotal) { // Que genero menos, al revez
                mejorDesp = desTotal;
                solucion.assign(listaPiezasResultante.begin(), listaPiezasResultante.end());        
            }
        }
        if(desTotal<0.0) break;
        if (mejorDespTotal>mejorDesp) { // Que genero menos, al revez
            mejorDespTotal = mejorDesp;   
            sinMej = 0;
        } else {
            sinMej++;
        }
//        imprimirSeparacion(MAX);
//        cout << " Mejor solución local: " << endl;
//        colocarPiezasEnOrden(solucion,listaStocks[0]);
//        desperdicio = calcularDesperdicio(solucion,listaStocks[0]);
//        cout<< "Desperdicio Sol. Local: "<< desperdicio <<endl;
        grafo.evaporarFeromonas(rho);
//        imprimirSeparacion(MAX);
    }
//    colocarPiezasEnOrden(solucion,listaStocks[0]);
    desperdicio = calcularDesperdicio(solucion,listaStocks[0]);
    cout<< desperdicio <<endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int nHormigas = 20;
    int maxIter = 50;
    float alpha = 1, beta = 5, rho = 0.9, Q=1;
    int tol = 50;
    
    vector<Pieza> listaPiezas = generarListaPiezas(numPiezas);
    vector<Stock> listaStocks = generarListaStocks(1);
    
    // Grafo
    Grafo grafo;
    // Agregar nodos al grafo
    for (int i = 0; i < numPiezas; ++i) {
        Nodo* nodo = new Nodo(to_string(i));
        nodo->id = i;
        grafo.agregarNodo(nodo);
    }
    // Generar grafo completo
    grafo.generarGrafoCompleto();
    // Imprimir las conexiones del grafo
    //grafo.imprimirConexionesCompacto();
    
    cout << "Lista de Piezas:\n";
    for (const Pieza& pieza : listaPiezas) {
        pieza.imprimirPieza();
    }
    cout << "\nLista de Stock:\n";
    listaStocks[0].imprimirStock();

    for(int i=0;i<=29;i++){
        AlgoritmoACO(nHormigas, maxIter, Q, alpha, beta, rho, tol, listaPiezas, listaStocks, grafo);
    }
    cout << "Ejecución del algoritmo ACO finalizada." << endl;
        
    return 0;
}
