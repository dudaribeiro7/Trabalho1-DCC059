#ifndef NO_H
#define NO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Aresta.h"
#include "Arco.h"

using namespace std;

//class Aresta;
class No
{

private:
    int id;           // ID contido em um nó.
    Aresta *prox;     // Aresta que liga o nó atual aos seus adjacentes. 
    Arco *proxArco;   // Arco que liga o nó atual aos seus adjacentes SUCESSORES. (Grafo Direcionado)
    int pesoNo;       // Peso do respectivo nó

public:
    No(int id);                         // Construtor da classe Nó.
    ~No();                              // Destrutor da classe Nó.
    int getId();                        // Retorna o ID do nó.
    void setId(int id);                 // Altera o ID do nó.
    int getPesoNo();                    // Retorna o peso do nó.
    void setPesoNo(int peso);           // Altera o peso do nó.
    Aresta *getProx();                  // Retorna o ponteiro da aresta que liga o nó ao adjacente.
    void setProx(Aresta *prox);         // Altera o nó adjacente.
    void adcAresta(No *n, int peso);    // Adiciona uma aresta na lista de arestas
    Arco *getProxArco();                // Retorna o ponteiro do arco que liga o nó ao adjacente SUCESSOR. (Grafo Direcionado)
    void setProxArco(Arco *proxArco);   // Altera o nó adjacente SUCESSOR. (Grafo Direcionado)
    void adcArco(No *n, int peso);      // Adiciona um arco na lista de arcos SUCESSORES (Grafo Direcionado)
};

#endif