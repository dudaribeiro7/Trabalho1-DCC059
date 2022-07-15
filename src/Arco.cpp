#include "Arco.h"

//Construtor
Arco::Arco(No *no, Arco *prox, int peso)
{
    this->no = no;
    this->prox = prox;
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

// Retorna o nó atual
No *Arco::getNo()
{
    return this->no;
}

// Determina o nó atual
void Arco::setNo(No *no)
{
    this->no = no;
}

// Retorna o próximo nó
Arco *Arco::getProx()
{
    return this->prox;
}

// Determina o próximo nó
void Arco::setProx(Arco *prox)
{
    this->prox = prox;
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