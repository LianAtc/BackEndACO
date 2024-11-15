#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stack>
#include <set>

#include "ClArista.h"
#include "ClNodo.h"
#include "ClGrafo.h"

#include "ClPieza.h"
#include "ClBase.h"

using namespace std;

int numPiezas = 40;
vector<vector<int>> matriz(numPiezas, vector<int>(numPiezas, -1));
vector<vector<int>> solucion(numPiezas, vector<int>(numPiezas, -1));
float anchoMayor,altoMayor;
double desTotal;

double calcularHeuristica(const Stock& stock, const Pieza& pieza) {
    double desperdicio;

    if(pieza.getH()>stock.getH()) return -1; // Si no entra de altura -1
    if(anchoMayor+pieza.getW()>stock.getW()) return -1; // Si es muy ancho no entra -1
    // Uso de piezas del mismo tamaño de alto que entren
    if(pieza.getH()== altoMayor && (pieza.getW()+anchoMayor <= stock.getW())) return -2;
    if(anchoMayor+pieza.getW()<= stock.getW()){
        if(altoMayor>pieza.getH()){
            desperdicio = (((altoMayor)*(anchoMayor+pieza.getW())) 
                    - ((anchoMayor*altoMayor)+
                    (pieza.getW()*pieza.getH()))) 
                    / ((altoMayor)*(anchoMayor+
                    pieza.getW()));
        }
        else{
            desperdicio = (((pieza.getH())*(anchoMayor+pieza.getW()) 
                    - (anchoMayor*altoMayor)+
                    (pieza.getW()* pieza.getH())))
                    / ((pieza.getH())*
                    (anchoMayor+pieza.getW()));
        }
    }
    
    return desperdicio;
}

const Pieza* buscarPiezaPorId(int id, const vector<Pieza>& listaPiezas) {
    for (const auto& pieza : listaPiezas) {
        if (pieza.getID() == id) {
            return &pieza; // Devolver la pieza si se encuentra
        }
    }
    return nullptr; // Si no se encuentra, devolver nullptr
}

double calcularDesperdicio(vector<Pieza>& listaPiezas, vector<vector<int>>& matriz, vector<Stock>& listaStocks) {
    double areaTotalPiezas = 0;

    // Recorrer la matriz y calcular el área de las piezas
    for (const auto& fila : matriz) {
        for (int id : fila) {
            const Pieza* pieza = buscarPiezaPorId(id, listaPiezas);
            if (pieza != nullptr) {
                areaTotalPiezas += pieza->calcularArea();
            }
        }
    }
    double areaStock = listaStocks[0].calcularArea();
    double desperdicio = areaStock - areaTotalPiezas;
    
    return desperdicio;
}

void ConstSol(float alpha, float beta, float rho, int tol, vector<Pieza>& listaPiezas2, vector<Stock>& listaStocks2, Grafo grafo) {
    Stock solucion;
    int numPiezaLista=0,indiceAleatorio=0,entra=0,a,b;
    float ancho,alto,menorH=100;
    int piezaEscogida,i=0,j=0,piezaPasada,intentos=0,indice;
    double feromonas,heuristica,probabillidad=100,mProb=0;
    vector<int> indicePiezaEscogida;
    
    vector<Pieza> listaPiezas = listaPiezas2;
    vector<Stock> listaStocks = listaStocks2;
    
    cout<<"Imprimir piezas:"<<endl;
    for (const Pieza& pieza : listaPiezas) {
        pieza.imprimirPieza();
    }
    
    cout<<"Imprimir stock: "<<endl;
    listaStocks[0].imprimirPiezas();
    
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
                listaPiezas[indice].imprimirPieza();
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
        for(int i=0; i<100;i++) cout<<"=";
        cout<<endl;
        cout<< "Pieza Aleatoria:" <<endl;
        cout<< "Indice : "<< indiceAleatorio <<endl;
                  
        // Defino la longitud más grande a cortar en guillotina
        anchoMayor = listaPiezas[indice].getW();
        altoMayor = listaPiezas[indice].getH();
        
        cout << "Ancho x Alto:" << anchoMayor << " , " << altoMayor<<endl;
        for(int i=0; i<100;i++) cout<<"=";
        cout<<endl;

        // Elimino pieza inicial
        auto it2 = std::find_if(listaPiezas.begin(), listaPiezas.end(), [indiceAleatorio](const Pieza& pieza) {
            return pieza.getID() == indiceAleatorio;
        });
        if (it2 != listaPiezas.end()) {
            listaPiezas.erase(it2);
        }
        matriz[i][j]=indiceAleatorio;
        i++;
        piezaPasada = indiceAleatorio;
        for (const Pieza& pieza2 : listaPiezas) { //Encajo pieza
            for(int i=0; i<100;i++) cout<<"=";
            cout<<endl;
            cout<< "Piezas restantes a probar: "<<endl;
            for (const Pieza& pieza : listaPiezas) { // Escoger una pieza
                feromonas= grafo.obtenerFeromonas(indiceAleatorio,pieza.getID());
                // Escojo la posibilidad de la mejor pieza a entrar
                heuristica = calcularHeuristica(listaStocks[0],pieza);
                probabillidad = (feromonas*alpha)+((1/heuristica)*beta);
                if(mProb<=probabillidad){    
                    mProb = probabillidad;
                    piezaEscogida = pieza.getID();
                    alto = pieza.getH();
                    ancho = pieza.getW();
                }
                if( heuristica != -1 ) menorH = heuristica;
                grafo.aumentarFeromonas(piezaPasada,pieza.getID(),0.001);
                pieza.imprimirPieza();
                if( heuristica == -2) break;
            }
            for(int i=0; i<100;i++) cout<<"=";
            cout<<endl;
            if (menorH == -1 || menorH == 100) break;
            matriz[i][j]=piezaEscogida;
            cout<< "Pieza Encajada: "<< piezaEscogida<< " ("<<alto<<"x"<<ancho<<")" <<endl;
            
            i++;

            if(altoMayor>alto){
                anchoMayor += ancho;
            }else{
                anchoMayor += ancho;
                altoMayor = alto;
            }
            
            cout<< "Espacio: " << altoMayor << " , " << anchoMayor<<endl;
            cout<< "Ancho y Alto Mayor: " << anchoMayor << " , "<<altoMayor<<endl;

            indicePiezaEscogida.push_back(piezaEscogida);
            piezaPasada = piezaEscogida;
            
            // Elimino pieza escogida
            auto it = std::find_if(listaPiezas.begin(), listaPiezas.end(), [piezaEscogida](const Pieza& pieza) {
                return pieza.getID() == piezaEscogida;
            });
            if (it != listaPiezas.end()) {
                listaPiezas.erase(it);
            }
            
            //desTotal+=heuristica;
            mProb=0;piezaEscogida=-1;menorH=100;
        }
        for(int i=0; i<100;i++) cout<<"=";
        cout<<endl;
        cout<<"Cambio de nivel"<<endl;
        i=0;
        listaStocks[0].setH(listaStocks[0].getH()-altoMayor); // Actualizo el  nuevo alto
        cout<<"Imprimir stock: "<<endl;
        listaStocks[0].imprimirPiezas();
        for(int i=0; i<100;i++) cout<<"=";
        cout<<endl;
        altoMayor=0;
        anchoMayor=0;
        j++;
    }
    desTotal = calcularDesperdicio(listaPiezas2,matriz,listaStocks2);
    cout<< "Desperdicio: "<< desTotal <<endl;
}

void AlgoritmoACO(int nHormigas, int maxIter, float alpha, float beta, float rho, int tol, vector<Pieza>& listaPiezas, vector<Stock>& listaStocks, Grafo grafo) {
    Stock Solucion,mejorSolucion;
    int sinMej = 0, mejorDesp=100000,i=0,j=0; // Actualizar a 100
    
    //Inicializo feromonas
    grafo.inicializarFeromonas(rho);
    
    for (int iter = 0; iter < maxIter && sinMej < tol; ++iter) {
        for (int h = 0; h < nHormigas; ++h) {
            cout << "Iniciando algoritmo ACO con " << h+1 << " hormigas..." << endl;
            ConstSol(alpha,beta,rho,tol,listaPiezas,listaStocks,grafo);
            if (mejorDesp>desTotal) { // Que genero menos, al revez
                mejorDesp = desTotal;
                for (int i = 0; i < (numPiezas-1); ++i) {
                    for (int j = 0; j < (numPiezas-1); ++j) {
                        solucion[i][j] = matriz[i][j];
                    }
                }
                sinMej = 0;
            } else {
                sinMej++;
            }
            for (int i = 0; i < (numPiezas-1); ++i) {
                for (int j = 0; j < (numPiezas-1); ++j) {
                    matriz[i][j] = -1;
                }
            }
            // Cada vez que encuentro una solucion evaporo las feromonas
            grafo.evaporarFeromonas(rho);
        }
    }
    
    cout<<"Solucion"<<endl;
    for (int j = 0; j < (numPiezas-1); ++j) {
        for (int i = 0; i < (numPiezas-1); ++i) {
            if(solucion[i][j] == -1) break;
            cout << solucion[i][j] << " "; // Debe imprimir mejor matriz, no matriz
            solucion[i][j] = -1;
        }
        cout << endl;  // Salto de línea después de cada fila
    }
    cout<<"Menor Desperdicio: "<< mejorDesp <<endl;
}

vector<Pieza> generarListaPiezas(int cantidad) {
    vector<Pieza> listaPiezas;
    vector<pair<float, float>> medidasDisponibles = {
        {45, 8.6}, {15, 7.5}, {40, 25.0}, {40, 8.0}
    };

    for (int i = 0; i < cantidad; ++i) {
        float x = 0;
        float y = 0;
        bool rotada = 0;

        // Elegir un par de medidas aleatoriamente
        int indiceAleatorio = rand() % medidasDisponibles.size();
        float w = medidasDisponibles[indiceAleatorio].first;
        float h = medidasDisponibles[indiceAleatorio].second;
        
        Pieza p(i, x, y, w, h, rotada);
        listaPiezas.push_back(p);
    }
    return listaPiezas;
}

vector<Stock> generarListaStocks(int cantidad) {
    vector<Stock> listaStocks;
    
    // Inicializar la semilla aleatoria
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < cantidad; ++i) {
        int w, h;
        
        // Elegir aleatoriamente entre las dos opciones de tamaño
        if (rand() % 2 == 0) {
            w = 60;
            h = 60;
        } else {
            w = 45;
            h = 45;
        }
        
        Stock s(w, h); // Crear el objeto Stock con las dimensiones seleccionadas
        listaStocks.push_back(s); // Agregar a la lista
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

int main() {
    srand(static_cast<unsigned>(time(0)));
    int nHormigas = 100;
    int maxIter = 100;
    float alpha = 1.0, beta = 5, rho = 0.4;
    int tol = 1;
    
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

    AlgoritmoACO(nHormigas, maxIter, alpha, beta, rho, tol, listaPiezas, listaStocks, grafo);
    cout << "Ejecución del algoritmo ACO finalizada." << endl;
    
    cout << "Lista de Piezas:\n";
    for (const Pieza& pieza : listaPiezas) {
        pieza.imprimirPieza();
    }
    cout << "\nLista de Stock:\n";
    listaStocks[0].imprimirStock();
        
    return 0;
}
