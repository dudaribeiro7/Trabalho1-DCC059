/*******************************************************************
 *   Defines
 *******************************************************************/
#ifndef NO_H
#define NO_H

/*******************************************************************
 *   Includes
 *******************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "aresta.h"

/*******************************************************************
 *   DECLARAÇÕES DOS METODOS
 *******************************************************************/

using namespace std;

class Aresta;
class No
{

private:
    int id;       // id contido em um nó.
    Aresta *prox; // Aresta que liga o nó atual aos seus adjacentes.
    int pesoNo;   // Peso do respectivo nó

public:
    No(int id);         // Construtor da classe Nó.
    ~No();              // Destrutor da classe Nó.
    int getId();        // Retorna o ID do nó.
    void setId(int id); // Altera o ID do nó.
    int getPesoNo();            //Retorna o peso do nó.
    void setPesoNo(int peso);   //Altera o peso do nó.
    Aresta *getProx();              // Retorna o ponteiro da aresta que liga o nó ao adjacente.
    void setProx(Aresta *prox);     // Altera o nó adjacente.
    void adcAresta(No *n, int peso);// adiciona uma aresta na lista de arestas
};

#endif