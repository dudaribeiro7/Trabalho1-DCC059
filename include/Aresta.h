#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "no.h"

using namespace std;

typedef struct // Criei essa classe só para remover os erros, tem que excluir depois !!!!!!!!!
{

}No;

class Aresta
{

private:
    No *no;       // Nó ao qual esta aponta (destino).
    Aresta *prox; // Próxima aresta que conecta o nó aos seus demais adjacentes.
    int peso;     // Peso do nó

public:
    Aresta(No *no, Aresta *prox, int peso); // Construtor
    ~Aresta();                              // Destrutor
    No *getNo();
    void setNo(No *no);
    Aresta *getProx();
    void setProx(Aresta *prox);
    int getPeso();
    void setPeso(int peso);
};

#endif