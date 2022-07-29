#include "Aresta.h"

// Construtor
// @param _no1/_no2 vértices aos quais a aresta está ligada
// @param _peso peso da aresta
Aresta::Aresta(No *_no1, No *_no2, int _peso)
{
    this->no1 = _no1;
    this->no2 = _no2;
    this->peso = _peso;
}

// Destrutor
Aresta::~Aresta()
{ 

}

// Retorna um dos nós ao qual a aresta está ligada
// @return No*
No* Aresta::getNo1()
{
    return this->no1;
}

// Modifica um dos nós ao qual a aresta está ligada
// @param _no1 nó que será colocado na aresta
void Aresta::setNo1(No *_no1)
{
    this->no1 = _no1;
}

// Retorna um dos nós ao qual a aresta está ligada
// @return No*
No* Aresta::getNo2()
{
    return this->no2;
}

// Modifica um dos nós ao qual a aresta está ligada
// @param _no2 nó que será colocado na aresta
void Aresta::setNo2(No *_no2)
{
    this->no2 = _no2;
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