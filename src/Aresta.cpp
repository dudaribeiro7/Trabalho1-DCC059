#include "aresta.h"

//Construtor
Aresta::Aresta(No *no, Aresta *prox, int peso)
{
    this->no = no;
    this->prox = prox;
    this->peso = peso;
}

//Destrutor
Aresta::~Aresta()
{
    if (prox != NULL)
    {
        delete prox;
    }
}

// Retorna o nó atual
No *Aresta::getNo()
{
    return this->no;
}

// Determina o nó atual
void Aresta::setNo(No *no)
{
    this->no = no;
}

// Retorna o próximo nó
Aresta *Aresta::getProx()
{
    return this->prox;
}

// Determina o próximo nó
void Aresta::setProx(Aresta *prox)
{
    this->prox = prox;
}

// Retorna o peso da aresta
int Aresta::getPeso()
{
    return this->peso;
}

// Determina o peso da aresta
void Aresta::setPeso(int peso)
{
    this->peso = peso;
}