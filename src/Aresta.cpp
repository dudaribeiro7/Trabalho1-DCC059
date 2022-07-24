#include "Aresta.h"

// Construtor
// @param _no vértice ao qual a aresta está ligada
// @param _peso peso da aresta
Aresta::Aresta(No *_no, int _peso)
{
    this->no = _no;
    this->peso = _peso;
}

// Destrutor
Aresta::~Aresta()
{
    delete no;
}

// Retorna um dos nós ao qual a aresta está ligada
// @return No*
No* Aresta::getNo()
{
    return this->no;
}

// Modifica um dos nós ao qual a aresta está ligada
// @param _no1 nó que será colocado na aresta
void Aresta::setNo(No *_no)
{
    this->no = _no;
}

// Retorna o peso da aresta
// @return int
int Aresta::getPeso()
{
    return this->peso;
}

// Modifica o peso da aresta
// @param _peso novo peso da aresta
void Aresta::setPeso(int _peso)
{
    this->peso = _peso;
}