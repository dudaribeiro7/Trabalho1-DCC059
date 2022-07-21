#include "Grafo.h"
#define infinito 999999999
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
    Aresta *aux;

    for (int i = 0; i < n_vertices; i++)
    {
        aux = grafo[i]->getProx();
        int cont = 0;

        while (aux != NULL)
        {
            cont++;
            aux = aux->getProx();
        }
    }
}

// TODO: @vitor-frnds
// @return Coeficiente de agrupamento médio do grafo
int Grafo::coeficienteAgrupamentoMedio()
{
    int coef = 0; // coeficiente de agrupamento local de cada vértice
    int som = 0;  // somatorio dos coeficientes de agrupamentos locais

    for (int i = 0; i < n_vertices; i++)
    {
        coef = coeficienteAgrupamentoLocal(i);
        som = som + coef;
        coef = 0;
    }

    return (som / n_vertices);
}

// TODO: @RiUza02
// @param inicio/destino dois IDs de vértices do grafo
// @return O caminho mínimo entre esses dois vértices usando o algoritmo de Dijkstra
void Grafo::dijkstra(int inicio, int destino)
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
        // varre todos os adijacentes do nó da interação atual e atualiza seus custos
        w = r;
        for (Aresta *aux = grafo[w]->getProx(); aux != NULL; aux = aux->getProx())
        {
            if (beta[aux->getNo()->getId()] > beta[w] + aux->getPeso())
            {
                beta[aux->getNo()->getId()] = beta[w] + aux->getPeso();
                pi[aux->getNo()->getId()] = w;
            }
        }

        // pega o primeiro nó que não esta no conjunto solução
        int flagMenor = 0;
        int contador = 0;
        while ((flagMenor == 0) && (contador < n_vertices))
        {
            if (fi[i] != 1)
            {
                r = contador;
                flagMenor = contador;
            }
            contador++;
        }

        // escolhe entre todos os nós do conjunto solução o menor deles
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

        // encerra a execução se possivel
        fi[r] = 1;
        if (w == destino)
        {
            flag = 1;
        }
    }

    // organiza o menor caminho
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

    // imprime a resposta
    for (int i = 0; i < solucao.size(); i++)
    {
        cout << " - " < pi[i] << " - "; 
    }
}

// TODO: @RiUza02
// @param id1/id2 dois IDs de vértices do grafo
// @return O caminho mínimo entre esses dois vértices usando o algoritmo de Floyd
void Grafo::floyd(int id1, int id2)
{
    int matrizAdj[n_vertices][n_vertices];
    No *auxNo;
    Aresta *auxAresta;
    int pi[n_vertices][n_vertices];

    // Inicialização da matriz e o vetor caminho
    for (int i = 0; i < this->getNumVertices(); i++)
    {
        for (int j = 0; j < this->getNumVertices(); j++)
        {
            if (i == j)
            {
                matrizAdj[i][j] = 0;
            }
            else
            {
                matrizAdj[i][j] = INT_MAX;
            }
            pi[i][j] = 0;
        }
    }

    // Inserindo os valores iniciais
    for (int i = 0; i < this->getNumVertices(); i++)
    {
        auxNo = grafo[i];
        auxAresta = auxNo->getProx();

        while (auxAresta != NULL)
        {
            matrizAdj[i][auxAresta->getNo()->getId()] = auxAresta->getPeso();
            auxAresta = auxAresta->getProx();
        }
    }

    // preenchimento dos valores de distancias
    for (int i = 0; i < this->getNumVertices(); i++)
    {
        for (int j = 0; j < this->getNumVertices(); j++)
        {
            for (int k = 0; k < this->getNumVertices(); k++)
            {
                if ((matrizAdj[j][i] != INT_MAX) && (matrizAdj[i][k] != INT_MAX))
                {
                    if (matrizAdj[j][k] > (matrizAdj[j][i] + matrizAdj[i][k]))
                    {
                        matrizAdj[j][k] = matrizAdj[j][i] + matrizAdj[i][k];
                        pi[j][k] = i;
                    }
                }
            }
        }
    }

    // imprime a resposta
    floydAux(id1, id2, pi)
}

void floydAux(int a, int b, int P[][])
{
    if (P[a][b] == b)
    {
        cout << b << " ";
        return;
    }
    floydAux(a, P[a][b], P);
    cout << b << " ";
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