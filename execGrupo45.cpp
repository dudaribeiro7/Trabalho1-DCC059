#include <iostream>
#include <stdio.h>

using namespace std;

#include "Grafo.h"

#define INPUT_POND_DIR "./input/ponderados/"
#define INPUT_NAO_POND_DIR "./input/nao_ponderados/"


void funcionalidades(char opc, Grafo *grafo);

void print_help(char *argv)
{
    cout << "Uso: " << argv << " <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>" << endl;
    cout << "Exemplo: " << argv << " grafo_1000_1.txt grafo_saida.txt 1 0 0" << endl;
    exit(0);
}

void print_menu(Grafo *grafo)
{
    cout << "---------- MENU ----------" << endl
         << endl;

    cout << "a) Parâmetro: um ID de um vértice de um grafo direcionado " << endl;
    cout << "   Saída: o fecho transitivo direto deste vértice." << endl
         << endl;

    cout << "b) Parâmetro: um ID de um vértice de um grafo direcionado." << endl;
    cout << "   Saída: o fecho transitivo indireto deste vértice." << endl
         << endl;

    cout << "c) Parâmetro: o ID de um vértice do grafo" << endl;
    cout << "   Saída: o coeficiente de agrupamento local do vértice" << endl
         << endl;

    cout << "d) Parâmetro: um grafo." << endl;
    cout << "   Saída: o coeficiente de agrupamento médio do grafo." << endl
         << endl;

    cout << "e) Parâmetro: dois IDs de vértices do grafo." << endl;
    cout << "   Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Djkstra." << endl
         << endl;

    cout << "f) Parâmetro: dois IDs de vértices do grafo." << endl;
    cout << "   Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Floyd." << endl
         << endl;

    cout << "g) Parâmetro: um subconjunto X de vértices de um grafo." << endl;
    cout << "   Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim." << endl
         << endl;

    cout << "h) Parâmetro: um subconjunto X de vértices do grafo." << endl;
    cout << "   Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal." << endl
         << endl;

    cout << "i) Parâmetro: um ID de vértice." << endl;
    cout << "   Saída: a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro, destacando as arestas de retorno." << endl
         << endl;

    cout << "Digite a opção da funcionalidade que deseja testar: ";
    char opc;
    cin >> opc;
    funcionalidades(opc, grafo);
}

void testarNovamente(char s_n, Grafo *grafo)
{
    switch (s_n)
    {
    case 's':
        print_menu(grafo);
        break;

    case 'n':
        exit(0);
        break;

    default:
        cout << "Opção inválida. Tente novamente, digitando uma opção válida (s ou n): ";
        cin >> s_n;
        testarNovamente(s_n, grafo);
        break;
    }
}

void funcionalidades(char opc, Grafo *grafo)
{
    int id, id1, id2, n;
    int coefA_local, coefA_medio;
    vector<int> X;

    switch (opc)
    {
    case 'a':
        if (grafo->isDirecionado())
        {
            cout << "Digite o ID de um vértice do grafo: ";
            cin >> id;
            vector<No *> fechoT_direto = grafo->fechoTransDir(id);

            // TODO: @marianaricha
            // imprimir o fecho transitivo direto do vertice.
        }
        else
            cout << "Esse grafo não é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;

        break;

    case 'b':
        if (grafo->isDirecionado())
        {
            cout << "Digite o ID de um vértice do grafo: ";
            cin >> id;
            vector<No *> fechoT_indireto = grafo->fechoTransInd(id);

            // TODO: @marianaricha
            // imprimir o fecho transitivo indireto do vertice.
        }
        else
            cout << "Esse grafo não é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;

        break;

    case 'c':
        cout << "Digite o ID de um vértice do grafo: ";
        cin >> id;
        coefA_local = grafo->coeficienteAgrupamentoLocal(id);
        cout << "O coeficiente de agrupamento local do nó " << id << " é igual a: " << coefA_local << endl;

        break;

    case 'd':
        coefA_medio = grafo->coeficienteAgrupamentoMedio();
        cout << "O coeficiente de agrupamento médio do grafo é igual a: " << coefA_medio << endl;

        break;

    case 'e':
        cout << "Digite o ID de dois vértices do grafo: ";
        cin >> id1 >> id2;
        grafo->dijkstra(id, id2);

        // TODO: @RiUza02
        // imprimir o caminho minimo entre os dois vertices
        // a propria função ja faz o serviço ~~ Yuri

        break;

    case 'f':
        cout << "Digite o ID de dois vértices do grafo: ";
        cin >> id1 >> id2;
        grafo->floyd(id, id2);

        // TODO: @RiUza02
        // imprimir o caminho minimo entre os dois vertices
        // a propria função ja faz o serviço ~~ Yuri

        break;

    case 'g':
        if (grafo->isDirecionado())
            cout << "Esse grafo é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
        else
        {
            cout << "Digite o número de vértices que você deseja que o subconjunto X de vértices tenha: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Digite o ID de um vértice a ser adicionado no subconjunto X de vértices: ";
                cin >> id;
                X.push_back(id);
            }
            grafo->prim(X);

            // TODO: @dudaribeiro7
            // imprimir a arvore geradora minima
        }

        break;

    case 'h':
        if (grafo->isDirecionado())
            cout << "Esse grafo é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
        else
        {
            cout << "Digite o número de vértices que você deseja que o subconjunto X de vértices tenha: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Digite o ID de um vértice a ser adicionado no subconjunto X de vértices: ";
                cin >> id;
                X.push_back(id);
            }
            grafo->kruskal(X);

            // TODO: @dudaribeiro7
            // imprimir a arvore geradora minima
        }

        break;

    case 'i':
        if (grafo->isDirecionado())
            cout << "Esse grafo é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
        else
        {
            cout << "Digite o ID de um vértice do grafo: ";
            cin >> id;
            grafo->caminhamentoProfundidade(id);

            // TODO: @marianaricha7
            // imprimir a arvore dada pela ordem de caminhamento em profundidade
            // a partir do nó dado por parametro, destacando as arestas de retorno
        }

        break;

    default:
        cout << "Opção inválida. Tente novamente, digitando uma opção válida (a, b, c, d, e, f, g, h ou i): ";
        cin >> opc;
        funcionalidades(opc, grafo);
        break;
    }

    cout << endl
         << "Deseja testar outra funcionalidade? (s/n)" << endl;
    char s_n;
    cin >> s_n;
    testarNovamente(s_n, grafo);
}

int main(int argc, char *argv[])
{
    string arquivo_entrada;
    string arquivo_saida;
    int opc_direc;
    int opc_peso_aresta;
    int opc_peso_nos;

    if (argc == 6)
    {
        arquivo_entrada = argv[1];
        arquivo_saida = argv[2];
        opc_direc = stoi(argv[3]);
        opc_peso_aresta = stoi(argv[4]);
        opc_peso_nos = stoi(argv[5]);
    }
    else
        print_help(argv[0]);

    string input;
    if(opc_peso_aresta == 1)
        input = INPUT_POND_DIR + arquivo_entrada;
    else
        input = INPUT_NAO_POND_DIR + arquivo_entrada;

    Grafo *grafo = new Grafo(input, opc_direc, opc_peso_aresta, opc_peso_nos);

    print_menu(grafo);

    return 0;
}