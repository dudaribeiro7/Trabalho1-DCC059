#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <math.h>

#include "No.h"

using namespace std;

class Grafo
{
    private:    
        No **grafo;       // vetor de vetores do tipo nó
        int n_vertices;   // número de vertices de cada grafo
        void leArquivo(string nomeArquivo); 

    public:
        Grafo(string nomeArquivo);
        ~Grafo();
        void printGrafo();
        bool verificaAresta(int id1, int id2);
        int getNumVertices();
        int coeficienteAgrupamentoLocal(int id);
        int coeficienteAgrupamentoMedio();
        void dijkstra(int id1, int id2);
        void floyd(int id1, int id2);
        void prim(vector<int> subconjunto);
        void kruskal(vector<int> subconjunto);
        void caminhamentoProfundidade(int id);
};

#endif