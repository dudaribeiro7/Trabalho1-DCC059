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
        No **grafo;       // vetor de vetores do tipo nó (lista de adjacência)
        int n_vertices;   // número de vertices do grafo
        bool direcionado;
        bool ponderadoArestas;
        bool ponderadoNos;
        
        void leArquivo(string nomeArquivo); 
        void floyd(int id1, int id2,int P[][]); // função auxiliar para o algoritmo de floyd
    public:
        Grafo(string nomeArquivo, int direc, int peso_aresta, int peso_nos);
        ~Grafo();
        void printGrafo();
        bool verificaAresta(int id1, int id2);
        bool verificaArco(int id1, int id2);
        int getNumVertices();
        No* fechoTransDir(int id);
        No* fechoTransInd (int id);
        int coeficienteAgrupamentoLocal(int id);
        int coeficienteAgrupamentoMedio();
        void dijkstra(int inicio, int destino);
        void floyd(int id1, int id2);
        void prim(vector<int> X);
        void kruskal(vector<int> X);
        void caminhamentoProfundidade(int id);
};

#endif