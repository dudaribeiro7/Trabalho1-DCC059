#include "Grafo.h"

// Função para ler o arquivo contendo o grafo
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
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

// Construtor
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
Grafo::Grafo(string nomeArquivo)
{
    leArquivo(nomeArquivo);
}

// Destrutor
Grafo::~Grafo()
{
    for (int i = 0; i < n_vertices; i++)
    {
        delete grafo[i];
    }

    delete[] grafo;
}

// Imprime o grafo na tela
void Grafo::printGrafo()
{
    for (int i = 0; i < n_vertices; i++)
    {
        cout << grafo[i]->getId() << " - ";
        Aresta *aux = grafo[i]->getProx();
        while (aux != NULL)
        {
            cout << aux->getNo()->getId() << " - ";
            aux = aux->getProx();
        }

        cout << endl;
    }
}

// Verifica se é possível existir uma aresta entre os nós.
// Elimina a possibilidade de existência de self-loops e multiarestas.
// @param id1 É a identificação do no 1 a ser verificado
// @param id2 É a identificação do no 2 a ser verificado
// @return true (se for possível) ou false (se não for possível, pois é multiaresta ou self-loop)
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

// Retorna o número de vértices do grafo
// @return n_vertices (int)
int Grafo::getNumVertices()
{
    return n_vertices;
}

// TODO: @vitor-frnds
// @param id ID de um vértice do grafo
// @return Coeficiente de agrupamento local do vértice
int Grafo::coeficienteAgrupamentoLocal(int id)
{

}

// TODO: @vitor-frnds
// @return Coeficiente de agrupamento médio do grafo
int Grafo::coeficienteAgrupamentoMedio()
{

}

// TODO: @RiUza02
// @param id1/id2 dois IDs de vértices do grafo
// @return O caminho mínimo entre esses dois vértices usando o algoritmo de Dijkstra
void Grafo::dijkstra(int id1, int id2)
{

}

// TODO: @RiUza02
// @param id1/id2 dois IDs de vértices do grafo
// @return O caminho mínimo entre esses dois vértices usando o algoritmo de Floyd
void Grafo::floyd(int id1, int id2)
{

}

// TODO: @dudaribeiro7
// @param X um subconjunto de vértices de um grafo
// @return Uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim
void Grafo::prim(vector<int> X)
{

}

// TODO: @dudaribeiro7
// @param X um subconjunto de vértices de um grafo
// @return Uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal
void Grafo::kruskal(vector<int> X)
{

}

// TODO: @marianaricha
// @param id um ID de vértice
// @return A árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro, destacando as arestas de retorno
void Grafo::caminhamentoProfundidade(int id)
{

}