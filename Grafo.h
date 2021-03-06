#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stack>
#include <vector>

#include "No.h"

using namespace std;

class Grafo
{
    private:    
        No **nos_grafo;         // Vetor de ponteiros do tipo No (lista de adjacência)
        int n_vertices;         // Número de vertices do grafo
        bool direcionado;       // Variável que determina se o grafo é direcionado ou não
        bool ponderadoArestas;  // Variável que determina se o grafo é ponderado nas arestas ou não
        bool ponderadoNos;      // Variável que determina se o grafo é ponderado nos vértices ou não
        
        void leArquivo(string nomeArquivo); 
        Grafo* subgrafoVerticeInduzido(vector<int> X);
        bool searchInVector(vector<int> vet, int id);
        bool searchNoInVector(vector<No*> vet, No* id);
        No* getNoInVector(No** _nos_grafo, int id);
        void cP(int id, bool v[], vector<No*> *vetor, int aux);
        void fechoaux(int id, bool v[], vector<No*> *vetor);


    public:
        Grafo(string nomeArquivo, int direc, int peso_aresta, int peso_nos);
        Grafo(No **_nos_grafo, int _n_vertices, bool _direc, bool _pesoAresta, bool _pesoNos);
        ~Grafo();
        void printGrafo();
        int getNumVertices();
        No** getNosGrafo();
        bool isDirecionado();
        bool isPonderadoArestas();
        bool isPonderadoNos();
        Aresta* arestaMenorPeso();
        vector<No*> fechoTransDir(int id);
        vector<No*> fechoTransInd (int id);
        float coeficienteAgrupamentoLocal(int id);
        float coeficienteAgrupamentoMedio();
        void dijkstra(int inicio, int destino, string arquivo_saida);
        void floyd(int id1, int id2, string arquivo_saida);
        void prim(vector<int> X, string arquivo_saida);
        void kruskal(vector<int> X, string arquivo_saida);
        vector<No*> caminhamentoProfundidade(int id, string arquivo_saida);
};

#endif