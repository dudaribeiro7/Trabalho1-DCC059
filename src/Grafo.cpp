#include "Grafo.h"
#define infinito 999999
// Função para ler o arquivo contendo o grafo
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
void Grafo::leArquivo(string nomeArquivo)
{
    // abertura do arquivo:
    fstream arq;
    arq.open(nomeArquivo, ios::in);
    if (!arq.is_open())
    {
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
    for (int i = 0; i < n_vertices; i++)
        grafo[i] = new No(i);

    // enquanto ainda houverem linhas a serem lidas:
    while (getline(arq, line))
    {
        // separa a linha, obtendo os nós e os pesos das arestas:
        stringstream ss(line);
        string aux;
        int cont = 0;
        vector<int> vet;
        while (getline(ss, aux, ' ')) // espaços separam os nós e peso da aresta no arquivo
        {
            vet[cont] = stoi(aux);
            cont++;
        }
        int no1 = vet[0];
        int no2 = vet[1];
        int peso;
        if (cont == 3)
            peso = vet[2];
        else
            peso = 1;

        if (verificaAresta(no1, no2))
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
    if (id1 == id2)
        return false;

    Aresta *aux = grafo[id1]->getProx();

    if (aux != NULL)
    {
        while (aux != NULL)
        {
            if (aux->getNo()->getId() == id2)
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
int *Grafo::dijkstra(int inicio, int destino)
{
    // https://www.youtube.com/watch?v=dIjGG_1vJYQ (video de onde eu tirei a resolução)
    vector<int> beta;
    vector<int> fi;
    vector<int> pi;
    int w, r;
    r = inicio;
    int flag = 0;

    for (int i = 0; i < n_vertices; i++)
    {
        beta.push_back(infinito);
        fi.push_back(0);
        pi.push_back(0);
    }
    beta[inicio] = 0;
    fi[inicio] = 1;

    while (flag == 0)
    {
        w = r;
        for (Aresta *aux = grafo[w]->getProx(); aux != NULL; aux = aux->getProx())
        {
            if (beta[aux->getNo()->getId()] > beta[w] + aux->getPeso())
            {
                beta[aux->getNo()->getId()] = beta[w] + aux->getPeso();
                pi[aux->getNo()->getId()] = w;
            }
        }
        int flagMenor = 0;
        while (flagMenor == 0)
        {
            if (fi[i] != 1)
            {
                r = i;
                flagMenor = 1;
            }
        }
        for (int i = 0; i < n_vertices; i++)
        {
            if (fi[i] != 1)
            {
                if ((beta[i] < beta[r]))
                {
                    r = i;
                }
            }
        }
        fi[r] = 1;
        if (w == destino)
        {
            flag = 1;
        }
    }

    vector<int> solucao;
    flag = 0;
    int aux1 = destino;
    int aux2 = pi[destino];
    solucao.push_back(aux1);
    while (flag == 0)
    {
        aux1 = aux2;
        aux2 = pi[aux1];
        solucao.push_back(aux1);
        if (aux1 == inicio)
        {
            flag = 1;
        }
    }
    return solucao;
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