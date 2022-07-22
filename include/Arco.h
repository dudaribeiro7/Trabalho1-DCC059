#ifndef ARCO_H
#define ARCO_H

#include <iostream>
#include <fstream>
#include <string>
#include "No.h"
//#include "Aresta.h"

using namespace std;
class Arco
{

private:
    No *no_origem;      // Origem do arco
    No *no_destino;     // Destino do arco
    Arco *proxArco;     // Próximo Arco que conecta o nó aos seus demais adjacentes.
    int peso;           // Peso do arco

public:
    Arco(No *no_origem, No *no_destino, Arco *prox, int peso);  // Construtor
    ~Arco();                                                    // Destrutor
    No *getNoOrigem();
    void setNoOrigem(No *no);
    No *getNoDestino();
    void setNoDestino(No *no);
    Arco *getProxArco();
    void setProxArco(Arco *prox);
    int getPeso();
    void setPeso(int peso);
};


#endif