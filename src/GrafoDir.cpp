#include "GrafoDir.h"

// Função para ler o arquivo contendo o grafo
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
void GrafoDir::leArquivo(string nomeArquivo)
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
    this->n_vertices = stoi(line);
    
    // instanciando o vetor de vetores com o numero de vertices:
    this->grafoDir = new No *[n_vertices];
    // preenche os vetores de nós:
    for(int i = 0; i < n_vertices; i++)
        this->grafoDir[i] = new No(i);
    
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

        if(verificaArco(no1, no2))
        {
            // conecta o nó ao arco que o liga ao seu nó adjacente SUCESSOR:
            this->grafoDir[no1]->adcArco(this->grafoDir[no1],this->grafoDir[no2], peso);
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
    if(id1 == id2)
        return false;
    
    Arco *aux = grafo[id1]->getProxArco();

    if(aux != NULL)
    {
        while(aux != NULL)
        {
            if(aux->getNo()->getId() == id2)
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

//TODO: @mariana_richa
//@param id ID de um vértice do grafo
//@return Fecho Transitivo Direto (vetor de vértices)
No* GrafoDir::fechoTransDir(int id){

}


//TODO: @mariana_richa
//@param id ID de um vértice do grafo
//@return Fecho Transitivo Indireto (vetor de vértices)
No* GrafoDir::fechoTransInd (int id){

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