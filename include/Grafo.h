#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdio.h>

#include "No.h"

using namespace std;

class Grafo
{
    private:    
        No **nos_grafo;       // vetor de ponteiros do tipo nó (lista de adjacência)
        int n_vertices;   // número de vertices do grafo
        bool direcionado;
        bool ponderadoArestas;
        bool ponderadoNos;
        
        void leArquivo(string nomeArquivo); 
        void floydAux(int id1, int id2, int P[][]); // função auxiliar para o algoritmo de floyd
        Grafo* subgrafoVerticeInduzido(vector<int> X);
        bool searchInVector(vector<int> vet, int id);
        bool searchNoInVector(vector<No*> vet, No* id);
        bool verificaAresta(No** _nos_grafo, int id1, int id2);
        bool verificaArco(No** _nos_grafo, int id1, int id2);
        void cP(int id, bool v[]);

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