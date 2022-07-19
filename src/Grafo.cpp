#include "Grafo.h"

void Grafo::leArquivo(string nomeArquivo)
{
    // abertura do arquivo:
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
        stringstream ss(line);
        string aux;
        int cont = 0;
        vector<int> vet;
        while(getline(ss, aux, ' ')) // espaços separam os nós e peso da aresta no arquivo
        {
            vet[cont] = stoi(aux);
            cont++;
        }
        int no1 = vet[0];
        int no2 = vet[1];
        int peso;
        if(cont == 3)
            peso = vet[2];
        else
            peso = 1;

        if(verificaAresta(no1, no2))
        {
            // conecta aos nós as arestas que os ligam aos seus adjacentes:
            grafo[no1]->adcAresta(grafo[no2], peso);
            grafo[no2]->adcAresta(grafo[no1], peso);
        }
    }
    arq.close();
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
    if(id1 == id2)
        return false;
    
    Aresta *aux = grafo[id1]->getProx();

    if(aux != NULL)
    {
        while(aux != NULL)
        {
            if(aux->getNo()->getId() == id2)
                return false;
            
            aux = aux->getProx();
        }
        return true;
    }
    else
        return true;
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