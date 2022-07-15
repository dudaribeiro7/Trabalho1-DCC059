#ifndef ARCO_H
#define ARCO_H

#include <iostream>
#include <fstream>
#include <string>
#include "No.h"
#include "Aresta.h"

using namespace std;

typedef struct
{
    // Criei essa classe só para remover os erros, tem que excluir depois !!!!!!!!!
}No;

class Arco
{

private:
    No *no;       // Origem do arco
    Arco *prox;   // Próxima Arco que conecta o nó aos seus demais adjacentes.
    int peso;     // Peso do arco

public:
    Arco(No *no, Arco *prox, int peso); // Construtor
    ~Arco();                                        // Destrutor
    No *getNo();
    void setNo(No *no);
    Arco *getProx();
    void setProx(Arco *prox);
    int getPeso();
    void setPeso(int peso);
};


#endif