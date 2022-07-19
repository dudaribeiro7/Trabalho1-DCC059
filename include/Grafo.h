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
        void leArquivo(string caminho);     //função para ler o arquivo contendo os grafos
        // vector<string> split(string str, char delimiter);
        No **grafo;                         // vetor de vetores do tipo nó
        int n_vertices;                     // aloca o número de vertices de cada grafo
        vector<int> sequenciaGrau;
        // bool verificaSolução(bool *nos);

    public:
        Grafo(string caminho);
        ~Grafo();
        void printGrafo();
        // int numArestas();
        // int numArestasTotal();
        // float grauMedioGrafo();
        bool verificaAresta(int id1, int id2);
        // vector<freq> frequenciaRelativa(); // Capta a sequencia de graus de cada nó e armazena em vetor.
        int getNumVertices();
        void buscaLargura(int origem);
        void buscaProfundidade(int origem);
        void dijkstra(int origem);
        void floyd();
        void prim();
        void kruskal();
};

#endif