#include "Arco.h"

//Construtor
Arco::Arco(No *no_origem, No *no_destino, Arco *prox, int peso)
{
    this->no_origem = no_origem;
    this->no_destino = no_destino;
    this->proxArco = prox;
    this->peso = peso;
}

//Destrutor
Arco::~Arco()
{
    if (prox != NULL)
    {
        delete prox;
    }
}

// Retorna o nó origem atual
No *Arco::getNoOrigem()
{
    return this->no_origem;
}

// Determina o nó origem atual
void Arco::setNoOrigem(No *no)
{
    this->no_origem = no;
}

// Retorna o nó destino atual
No *Arco::getNoDestino()
{
    return this->no_destino;
}

// Determina o nó destino atual
void Arco::setNoDestino(No *no)
{
    this->no_destino = no;
}

// Retorna o próximo nó
Arco *Arco::getProxArco()
{
    return this->proxArco;
}

// Determina o próximo nó
void Arco::setProxArco(Arco *prox)
{
    this->proxArco = prox;
}

// Retorna o peso da Arco
int Arco::getPeso()
{
    return this->peso;
}

// Determina o peso da Arco
void Arco::setPeso(int peso)
{
    this->peso = peso;
}