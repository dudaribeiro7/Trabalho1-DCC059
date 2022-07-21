#include "GrafoDir.h"

// Função para ler o arquivo contendo o grafo
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
void GrafoDir::leArquivo(string nomeArquivo)
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
    this->n_vertices = stoi(line);

    // instanciando o vetor de vetores com o numero de vertices:
    this->grafoDir = new No *[n_vertices];
    // preenche os vetores de nós:
    for (int i = 0; i < n_vertices; i++)
        this->grafoDir[i] = new No(i);

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

        if (verificaArco(no1, no2))
        {
            // conecta o nó ao arco que o liga ao seu nó adjacente SUCESSOR:
            this->grafoDir[no1]->adcArco(this->grafoDir[no1], this->grafoDir[no2], peso);
        }
    }
    arq.close();
}

// Construtor
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
GrafoDir::GrafoDir(string nomeArquivo)
{
    leArquivo(nomeArquivo);
}

// Destrutor
GrafoDir::~GrafoDir()
{
    for (int i = 0; i < n_vertices; i++)
    {
        delete grafoDir[i];
    }

    delete[] grafoDir;
}

// Imprime o grafo na tela
void GrafoDir::printGrafoDir()
{
    for (int i = 0; i < n_vertices; i++)
    {
        cout << grafoDir[i]->getId() << " -> ";
        Arco *aux = grafoDir[i]->getProxArco();
        while (aux != NULL)
        {
            cout << aux->getNo()->getId() << " -> ";
            aux = aux->getProxArco();
        }

        cout << endl;
    }
}

// Verifica se é possível existir um arco entre os nós.
// Elimina a possibilidade de existência de self-loops e multiarcos.
// @param id1 É a identificação do no 1 a ser verificado
// @param id2 É a identificação do no 2 a ser verificado
// @return true (se for possível) ou false (se não for possível, pois é multiarco ou self-loop)
bool GrafoDir::verificaArco(int id1, int id2)
{
    if (id1 == id2)
        return false;

    Arco *aux = grafo[id1]->getProxArco();

    if (aux != NULL)
    {
        while (aux != NULL)
        {
            if (aux->getNo()->getId() == id2)
                return false;

            aux = aux->getProxArco();
        }
        return true;
    }
    else
        return true;
}

// Retorna o número de vértices do grafo
// @return n_vertices (int)
int GrafoDir::getNumVertices()
{
    return n_vertices;
}

// TODO: @mariana_richa
//@param id ID de um vértice do grafo
//@return Fecho Transitivo Direto (vetor de vértices)
No *GrafoDir::fechoTransDir(int id)
{
}

// TODO: @mariana_richa
//@param id ID de um vértice do grafo
//@return Fecho Transitivo Indireto (vetor de vértices)
No *GrafoDir::fechoTransInd(int id)
{
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
    // https://www.youtube.com/watch?v=dIjGG_1vJYQ (video de onde eu tirei a resolução)
    vector<int> beta;
    vector<int> fi;
    vector<int> pi;
    int w, r, encerra;
    encerra = 0;
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

    while ((flag == 0) && (encerra < n_vertices))
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
        encerra++;
    }

    // organiza e envia o menor caminho
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