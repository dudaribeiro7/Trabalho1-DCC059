#include "no.h"

// Identificação do no e inicialização do no
No::No(int id)
{
    this->id = id;
    this->prox = NULL;
}

// Destrutor do objeto No
No::~No()
{
    if (prox != NULL)
    {
        delete prox;
    }
}

// Retorna o id do nó atual
int No::getId()
{
    return this->id;
}

// Modifica o id do nó atual
void No::setId(int id)
{
    this->id = id;
}

// Determina o peso do nó atual
void No::setPesoNo(int peso)
{
    this->pesoNo = peso;
}

// Retorna o peso do nó atual
int No::getPesoNo()
{
    return this->pesoNo;
}

// Retorna o proximo nó da lista encadeada de nós
Aresta *No::getProx()
{
    return this->prox;
}

// Determina o proximo nó da lista encadeadad de nós
void No::setProx(Aresta *prox)
{
    this->prox = prox;
}

// Adiciona aresta na lista encadeada das arestas
void No::adcAresta(No *n, int peso)
{
    Aresta *a = new Aresta(n, this->getProx(), peso);
    this->setProx(a);
}