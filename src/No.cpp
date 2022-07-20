#include "No.h"

// Identificação do no e inicialização do no
No::No(int id)
{
    this->id = id;
    this->prox = NULL;
    this->proxArco = NULL;
}

// Destrutor do objeto No
No::~No()
{
    if (prox != NULL)
    {
        delete prox;
    }

    if (proxArco != NULL)
    {
        delete proxArco;
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

// Retorna aresta da lista encadeada das arestas
Aresta *No::getProx()
{
    return this->prox;
}

// Determina a proxima aresta da lista encadeada de arestas
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

// Retorna o arco SUCESSOR da lista encadeada de arcos
Arco *No::getProxArco()
{
    return this->proxArco;
}

// Determina o proximo arco SUCESSOR da lista encadeada de arcos
void No::setProxArco(Arco *proxArco)
{
    this->proxArco = proxArco;
}

// Adiciona arco na lista encadeada de arcos SUCESSORES
void No::adcArco(No *n1, No *n2, int peso)
{
    Arco *a = new Arco(n1, n2, this->getProxArco(), peso);
    this->setProxArco(a);
}