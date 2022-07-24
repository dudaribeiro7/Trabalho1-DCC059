#include "Arco.h"

// Construtor
// @param _no_destino vértice de destino do arco
// @param _peso peso do arco
Arco::Arco(No *_no_destino, int _peso)
{
    this->no_destino = _no_destino;
    this->peso = _peso;
}

// Destrutor
Arco::~Arco()
{
    delete no_destino;
}

// Retorna o nó destino atual
// @return  No*
No* Arco::getNoDestino()
{
    return this->no_destino;
}

// Modifica o nó destino atual
// @param no nó de destino a ser colocado no arco
void Arco::setNoDestino(No *no)
{
    this->no_destino = no;
}

// Retorna o peso da Arco
// @return int
int Arco::getPeso()
{
    return this->peso;
}

// Determina o peso da Arco
// @param _peso novo peso do arco
void Arco::setPeso(int _peso)
{
    this->peso = _peso;
}