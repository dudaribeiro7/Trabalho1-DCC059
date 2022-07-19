#include "Grafo.h"

void Grafo::leArquivo(string nomeArquivo)
{
    fstream arq;
    arq.open(nomeArquivo, ios::in);
    if(!arq.is_open()){
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    string line;
    getline(arq, line);
    // a primeira linha do arquivo é o numero de vertices do grafo:
    n_vertices = stoi(line);
    
    // instanciando o vetor de vetores com o numero de vertices:
    grafo = new No *[n_vertices];
    // preenche os vetores de nós:
    for(int i = 0; i < n_vertices; i++)
        grafo[i] = new No(i);
    
    // enquanto ainda houverem linhas a serem lidas:
    while(getline(arq, line))
    {
        // separa a linha, obtendo os nós e os pesos das arestas:
        
    }
}

Grafo::Grafo(string caminho)
{

}

Grafo::~Grafo()
{

}

void Grafo::printGrafo()
{

}

bool Grafo::verificaAresta(int id1, int id2)
{

}

int Grafo::getNumVertices()
{

}

void Grafo::buscaLargura(int origem)
{

}

void Grafo::buscaProfundidade(int origem)
{

}

void Grafo::dijkstra(int origem)
{

}

void Grafo::floyd()
{

}

void Grafo::prim()
{

}

void Grafo::kruskal()
{

}