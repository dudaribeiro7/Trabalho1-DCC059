#include "No.h"

// Construtor da classe No
// @param _id ID do novo nó
// @param _peso peso do novo nó
No::No(int _id, int _peso)
{
    id = _id;
    pesoNo = _peso;
    grau = 0;
    grau_entrada = 0;
    grau_saida = 0;
}

// Destrutor do objeto No
No::~No()
{
    for(int i=0; i<arestas.size(); i++)
        delete arestas[i];
    if(!arestas.empty())
        arestas.clear();

    for(int i=0; i<arcos.size(); i++)
        delete arcos[i];
    if(!arcos.empty())
        arcos.clear();

    for(int i=0; i<nos_adjacentes.size(); i++)
        delete nos_adjacentes[i];
    if(!nos_adjacentes.empty())
        nos_adjacentes.clear();
}

// Retorna o ID do nó
// @return int
int No::getId()
{
    return this->id;
}

// Modifica o ID do nó
// @param id novo ID a ser colocado no nó
void No::setId(int id)
{
    this->id = id;
}

// Retorna o grau do nó
// @return int
int No::getGrau()
{
    return this->grau;
}

// Modifica o grau do nó
// @param _grau novo grau do nó
void No::setGrau(int _grau)
{
    this->grau = _grau;
}

// Incrementa em uma unidade o grau do nó
void No::incrementaGrau()
{
    this->grau++; 
}

// Retorna o grau de entrada do nó
// @return int
int No::getGrauEntrada()
{
    return this->grau_entrada;
}

// Modifica o grau de entrada do nó
// @param _grau_entrada novo grau de entrada do nó
void No::setGrauEntrada(int _grau_entrada)
{
    this->grau_entrada = _grau_entrada;
}

// Incrementa em uma unidade o grau de entrada do nó
void No::incrementaGrauEntrada()
{
    this->grau_entrada++; 
}

// Retorna o grau de saida do nó
// @return int
int No::getGrauSaida()
{
    return this->grau_saida;
}

// Modifica o grau de saida do nó
// @param _grau_saida novo grau de saida do nó
void No::setGrauSaida(int _grau_saida)
{
    this->grau_saida = _grau_saida;
}

// Incrementa em uma unidade o grau de saida do no
void No::incrementaGrauSaida()
{
    this->grau_saida++; 
}

// Retorna o peso do nó
// @return int
int No::getPesoNo()
{
    return this->pesoNo;
}

// Modifica o peso do nó
// @param peso novo peso a ser colocado no nó
void No::setPesoNo(int peso)
{
    this->pesoNo = peso;
}

// Retorna o vetor contendo as arestas ligadas ao nó
// @return vector<Aresta*>
vector<Aresta*> No::getArestas()
{
    return this->arestas;
}

Aresta* No::getPrimeiraAresta()
{
    return arestas[0];
}

// Adiciona aresta ao nó
// @param n nó adjacente ao nó atual, ligados pela aresta que será adicionada
// @param peso peso da aresta a ser adicionada
void No::adcAresta(No *n, int peso)
{
    Aresta *aux = new Aresta(this, n, peso);
    this->arestas.push_back(aux);
    this->nos_adjacentes.push_back(n);
    this->incrementaGrau();
    delete aux;
}

// Retorna o vetor contendo os arcos que saem do nó
// @return vector<Arco*>
vector<Arco*> No::getArcos()
{
    return this->arcos;
}

// Adiciona arco ao nó, que é o nó origem do arco
// @param n nó destino do arco
void No::adcArco(No *n, int peso)
{
    Arco *aux = new Arco(n, peso);
    this->arcos.push_back(aux);
    this->nos_sucessores.push_back(n);
    this->incrementaGrauSaida();
    n->incrementaGrauEntrada();
    delete aux;
}

vector<No*> No::getNosAdj()
{
    return this->nos_adjacentes;
}

vector<No*> No::getNosSuc()
{
    return this->nos_sucessores;
}