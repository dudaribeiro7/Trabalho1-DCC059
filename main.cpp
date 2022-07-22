#include <iostream>
#include <stdio.h>

using namespace std;

#include "Grafo.h"
#include "GrafoDir.h"

void print_help(char *argv)
{
    cout << "Uso: " << argv << " <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>" << endl;
    cout << "Exemplo: " << argv << " grafo_1000_1.txt grafo_saida.txt 1 0 0" << endl;
    exit(0);
}

int main(int argc, char *argv[])
{
    if(argc == 6)
    {
        string arquivo_entrada = argv[1];
        string arquivo_saida = argv[2];
        int opc_direc = stoi(argv[3]);
        int opc_peso_aresta = stoi(argv[4]);
        int opc_peso_nos = stoi(argv[5]);
    }
    else
        print_help(argv[0]);
    
    

    return 0;
}