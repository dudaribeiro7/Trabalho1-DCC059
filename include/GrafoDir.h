#ifndef GRAFODIR_H
#define GRAFODIR_H

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

class GrafoDir
{
    private:    
        No **grafoDir;       // vetor de vetores do tipo nó (LISTA DE ADJACÊNCIA SUCESSORA)
        int n_vertices;   // número de vertices do grafo
        void leArquivo(string nomeArquivo); 

    public:
        GrafoDir(string nomeArquivo);
        ~GrafoDir();
        void printGrafoDir();
        bool verificaArco(int id1, int id2);
        int getNumVertices();
        No* fechoTransDir(int id);
        No* fechoTransInd (int id);
        int coeficienteAgrupamentoLocal(int id);
        int coeficienteAgrupamentoMedio();
        void dijkstra(int id1, int id2);
        void floyd(int id1, int id2);
        void prim(vector<int> subconjunto);
        void kruskal(vector<int> subconjunto);
        void caminhamentoProfundidade(int id);
        
};

#endif