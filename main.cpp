#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#include "Grafo.h"

void print_help(char *argv)
{
    cout << "Uso: " << argv << " <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>" << endl;
    cout << "Exemplo: " << argv << " grafo_1000_1.txt grafo_saida.txt 1 0 0" << endl;
    exit(0);
}

int main(int argc, char *argv[])
{
    string arquivo_entrada;
    string arquivo_saida;
    int opc_direc;
    int opc_peso_aresta;
    int opc_peso_nos;

    if(argc == 6)
    {
        arquivo_entrada = argv[1];
        arquivo_saida = argv[2];
        opc_direc = stoi(argv[3]);
        opc_peso_aresta = stoi(argv[4]);
        opc_peso_nos = stoi(argv[5]);
    }
    else
        print_help(argv[0]);

    Grafo *grafo = new Grafo(arquivo_entrada, opc_direc, opc_peso_aresta, opc_peso_nos);

    // Inicializa o gerador de números aleatórios com o valor da função time(NULL).
    // Desta forma, a cada execução o valor aleatório gerado será diferente.
    srand(time(NULL));
    // Gera valores aleatórios entre 0 e o nº total de vertices do grafo:
    int id = rand() % grafo->getNumVertices();
    int id2 = rand() % grafo->getNumVertices();

    /*
    -----------------------------------------------------------------------------------------------------
    Funcionalidades A e B:
    -----------------------------------------------------------------------------------------------------
    */
    if(opc_direc == 1)
    {
        No *fechoT_direto = grafo->fechoTransDir(id);
        No *fechoT_indireto = grafo->fechoTransInd(id);
    }

    /*
    -----------------------------------------------------------------------------------------------------
    Funcionalidades C e D:
    -----------------------------------------------------------------------------------------------------
    */
    int coefA_local = grafo->coeficienteAgrupamentoLocal(id);
    int coefA_medio = grafo->coeficienteAgrupamentoMedio();

    /*
    -----------------------------------------------------------------------------------------------------
    Funcionalidades E e F:
    -----------------------------------------------------------------------------------------------------
    */
    grafo->dijkstra(id, id2);
    grafo->floyd(id, id2);

    /*
    -----------------------------------------------------------------------------------------------------
    Funcionalidades G e H:
    -----------------------------------------------------------------------------------------------------
    */
    vector<int> X; //subconjunto de vértices
    int n = rand() % 100; // número de vertices do subconjunto X (valor aleatório entre 0 e 100)
    for(int i=0; i<n; i++)
        X.push_back(rand() % grafo->getNumVertices());
    grafo->prim(X);
    grafo->kruskal(X);
    
    /*
    -----------------------------------------------------------------------------------------------------
    Funcionalidade I:
    -----------------------------------------------------------------------------------------------------
    */
    grafo->caminhamentoProfundidade(id);

    return 0;   
}