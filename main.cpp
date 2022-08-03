#include <iostream>
#include <stdio.h>

using namespace std;

#include "Grafo.h"

#define INPUT_POND_DIR "./input/ponderados/"
#define INPUT_NAO_POND_DIR "./input/nao_ponderados/"


void funcionalidades(char opc, Grafo *grafo, string arquivo_saida);

void print_help(char *argv)
{
    std::cout << "Uso: " << argv << " <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>" << endl;
    std::cout << "Exemplo: " << argv << " grafo_1000_1.txt grafo_saida.txt 1 0 0" << endl;
    exit(0);
}

void print_menu(Grafo *grafo, string arquivo_saida)
{
    std::cout << "------------------------------ MENU ------------------------------" << endl
         << endl;

    std::cout << "a) Parâmetro: um ID de um vértice de um grafo direcionado " << endl;
    std::cout << "   Saída: o fecho transitivo direto deste vértice." << endl
         << endl;

    std::cout << "b) Parâmetro: um ID de um vértice de um grafo direcionado." << endl;
    std::cout << "   Saída: o fecho transitivo indireto deste vértice." << endl
         << endl;

    std::cout << "c) Parâmetro: o ID de um vértice do grafo" << endl;
    std::cout << "   Saída: o coeficiente de agrupamento local do vértice" << endl
         << endl;

    std::cout << "d) Parâmetro: um grafo." << endl;
    std::cout << "   Saída: o coeficiente de agrupamento médio do grafo." << endl
         << endl;

    std::cout << "e) Parâmetro: dois IDs de vértices do grafo." << endl;
    std::cout << "   Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Djkstra." << endl
         << endl;

    std::cout << "f) Parâmetro: dois IDs de vértices do grafo." << endl;
    std::cout << "   Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Floyd." << endl
         << endl;

    std::cout << "g) Parâmetro: um subconjunto X de vértices de um grafo." << endl;
    std::cout << "   Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim." << endl
         << endl;

    std::cout << "h) Parâmetro: um subconjunto X de vértices do grafo." << endl;
    std::cout << "   Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal." << endl
         << endl;

    std::cout << "i) Parâmetro: um ID de vértice." << endl;
    std::cout << "   Saída: a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro, destacando as arestas de retorno." << endl
         << endl;

    std::cout << "Digite a opção da funcionalidade que deseja testar: ";
    char opc;
    std::cin >> opc;
    funcionalidades(opc, grafo, arquivo_saida);
}

void testarNovamente(char s_n, Grafo *grafo, string arquivo_saida)
{
    switch (s_n)
    {
    case 's':
        print_menu(grafo, arquivo_saida);
        break;

    case 'n':
        exit(0);
        break;

    default:
        std::cout << "Opção inválida. Tente novamente, digitando uma opção válida (s ou n): ";
        std::cin >> s_n;
        testarNovamente(s_n, grafo, arquivo_saida);
        break;
    }
}

bool searchInVector(vector<int> vet, int id)
{
    for (int i = 0; i < vet.size(); i++)
        if (vet[i] == id)
            return true;
    return false;
}

void funcionalidades(char opc, Grafo *grafo, string arquivo_saida)
{
    int id, id1, id2, n;
    float coefA_local, coefA_medio;
    vector<int> X;

    ofstream arq_out;
    arq_out.open(arquivo_saida, ios::app);
    if(!arq_out.is_open())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO DE SAIDA" << endl;
        exit(0);
    }

    switch (opc)
    {
    case 'a':
        if (grafo->isDirecionado())
        {
            std::cout << "Digite o ID de um vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id;
            while(id >= grafo->getNumVertices() || id < 0)
            {
                std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id;
            }
            vector<No *> fechoT_direto = grafo->fechoTransDir(id);

            std::cout << "f+(" << id << ") = {";
            for(int i = 0; i < fechoT_direto.size(); i++)
            {
                std::cout << fechoT_direto[i]->getId();
                if(i+1 < fechoT_direto.size())
                    std::cout << ", ";
            }
            std::cout << "}" << endl;

            arq_out << "Funcionalidade a) Fecho Transitivo Direto:" << endl;
            arq_out << "f+(" << id << ") = {";
            for(int i = 0; i < fechoT_direto.size(); i++)
            {
                arq_out << fechoT_direto[i]->getId();
                if(i+1 < fechoT_direto.size())
                    arq_out << ", ";
            }
            arq_out << "}" << endl << endl;

        }
        else
        {
            std::cout << "Esse grafo não é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
            arq_out << "Funcionalidade a) Fecho Transitivo Direto:" << endl;
            arq_out << "Esse grafo não é direcionado. Logo, não é possível realizar esta funcionalidade." << endl << endl;
        }

        break;

    case 'b':
        if (grafo->isDirecionado())
        {
            std::cout << "Digite o ID de um vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id;
            while(id >= grafo->getNumVertices() || id < 0)
            {
                std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id;
            }
            vector<No *> fechoT_indireto = grafo->fechoTransInd(id);
            std::cout << "f-(" << id << ") = {";
            for(int i = 0; i < fechoT_indireto.size(); i++)
            {
                std::cout << fechoT_indireto[i]->getId();
                if(i+1 < fechoT_indireto.size())
                    std::cout << ", ";
            }
            std::cout << "}" << endl;

            arq_out << "Funcionalidade b) Fecho Transitivo Indireto:" << endl;
            arq_out << "f+(" << id << ") = {";
            for(int i = 0; i < fechoT_indireto.size(); i++)
            {
                arq_out << fechoT_indireto[i]->getId();
                if(i+1 < fechoT_indireto.size())
                    arq_out << ", ";
            }
            arq_out << "}" << endl << endl;
        }
        else
        {
            std::cout << "Esse grafo não é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
            arq_out << "Funcionalidade b) Fecho Transitivo Indireto:" << endl;
            arq_out << "Esse grafo não é direcionado. Logo, não é possível realizar esta funcionalidade." << endl << endl;
        }

        break;

    case 'c':
        std::cout << "Digite o ID de um vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
        std::cin >> id;
        while(id >= grafo->getNumVertices() || id < 0)
        {
            std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id;
        }
        coefA_local = grafo->coeficienteAgrupamentoLocal(id);
        std::cout << "O coeficiente de agrupamento local do nó " << id << " é igual a " << coefA_local << endl;

        arq_out << "Funcionalidade c) Coeficiente de Agrupamento Local:" << endl;
        arq_out << "O coeficiente de agrupamento local do nó " << id << " é igual a " << coefA_local << endl << endl;

        break;

    case 'd':
        coefA_medio = grafo->coeficienteAgrupamentoMedio();
        std::cout << "O coeficiente de agrupamento médio do grafo é igual a " << coefA_medio << endl;

        arq_out << "Funcionalidade d) Coeficiente de Agrupamento Médio:" << endl;
        arq_out << "O coeficiente de agrupamento médio do grafo é igual a " << coefA_local << endl << endl;

        break;

    case 'e':
        std::cout << "Digite o ID de um vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
        std::cin >> id1;
        while(id1 >= grafo->getNumVertices() || id1 < 0)
        {
            std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id1;
        }
        std::cout << "Digite o ID de outro vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ", diferente de " << id1 << ": ";
        std::cin >> id2;
        while(id2 >= grafo->getNumVertices() || id2 < 0)
        {
            std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id2;
        }
        while(id2 == id1)
        {
            std::cout << "Esse vértice já foi passado. Por favor, tente novamente com um valor diferente: ";
            std::cin >> id2;
            while(id2 >= grafo->getNumVertices() || id2 < 0)
            {
                std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id2;
            }
        }
        arq_out << "Funcionalidade e) Caminho Mínimo com algoritmo de Dijkstra:" << endl;
        arq_out << "Caminho entre os vértices " << id1 << " e " << id2 << ":" << endl;
        grafo->dijkstra(id1, id2, arquivo_saida);
        arq_out << endl << endl;;

        break;

    case 'f':
        std::cout << "Digite o ID de um vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
        std::cin >> id1;
        while(id1 >= grafo->getNumVertices() || id1 < 0)
        {
            std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id1;
        }
        std::cout << "Digite o ID de outro vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ", diferente de " << id1 << ": ";
        std::cin >> id2;
        while(id2 >= grafo->getNumVertices() || id2 < 0)
        {
            std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id2;
        }
        while(id2 == id1)
        {
            std::cout << "Esse vértice já foi passado. Por favor, tente novamente com um valor diferente: ";
            std::cin >> id2;
            while(id2 >= grafo->getNumVertices() || id2 < 0)
            {
                std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id2;
            }
        }
        arq_out << "Funcionalidade f) Caminho Mínimo com algoritmo de Floyd:" << endl;
        arq_out << "Caminho entre os vértices " << id1 << " e " << id2 << ":" << endl;
        grafo->floyd(id1, id2, arquivo_saida);
        arq_out << endl << endl;

        break;

    case 'g':
        if (grafo->isDirecionado())
            std::cout << "Esse grafo é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
        else
        {
            std::cout << "Digite o número de vértices que você deseja que o subconjunto X de vértices tenha: ";
            std::cin >> n;
            while(n > grafo->getNumVertices() || n < 1)
            {
                std::cout << "Valor inválido. Por favor, tente novamente, digitando um valor entre 1 e " << grafo->getNumVertices() << ": ";
                std::cin >> n;
            }
            for (int i = 0; i < n; i++)
            {
                std::cout << "Digite o ID do " << i+1 << "º vértice a ser adicionado no subconjunto X de vértices, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id;
                while(id >= grafo->getNumVertices() || id < 0)
                {
                    std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                    std::cin >> id;
                }
                while(searchInVector(X, id))
                {
                    std::cout << "Esse vértice já foi adicionado ao subconjunto X. Por favor, tente novamente: ";
                    std::cin >> id;
                    while(id >= grafo->getNumVertices() || id < 0)
                    {
                        std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                        std::cin >> id;
                    }
                }
                X.push_back(id);
            }
            arq_out << "Funcionalidade g) Árvore Geradora Mínima com algoritmo de Prim:" << endl;
            arq_out << "Subconjunto de vértices: X = {";
            for(int i = 0; i < X.size(); i++)
            {
                arq_out << X[i];
                if(i+1 < X.size())
                    arq_out << ", ";
            }
            arq_out << "}" << endl;
            grafo->prim(X, arquivo_saida);
            arq_out << endl << endl;
        }

        break;

    case 'h':
        if (grafo->isDirecionado())
            std::cout << "Esse grafo é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
        else
        {
            std::cout << "Digite o número de vértices que você deseja que o subconjunto X de vértices tenha: ";
            std::cin >> n;
            while(n > grafo->getNumVertices() || n < 1)
            {
                std::cout << "Valor inválido. Por favor, tente novamente, digitando um valor entre 1 e " << grafo->getNumVertices() << ": ";
                std::cin >> n;
            }
            for (int i = 0; i < n; i++)
            {
                std::cout << "Digite o ID do " << i+1 << "º vértice a ser adicionado no subconjunto X de vértices, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id;
                while(id >= grafo->getNumVertices() || id < 0)
                {
                    std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                    std::cin >> id;
                }
                while(searchInVector(X, id))
                {
                    std::cout << "Esse vértice já foi adicionado ao subconjunto X. Por favor, tente novamente: ";
                    std::cin >> id;
                    while(id >= grafo->getNumVertices() || id < 0)
                    {
                        std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                        std::cin >> id;
                    }
                }
                X.push_back(id);
            }
            arq_out << "Funcionalidade h) Árvore Geradora Mínima com algoritmo de Kruskal:" << endl;
            arq_out << "Subconjunto de vértices: X = {";
            for(int i = 0; i < X.size(); i++)
            {
                arq_out << X[i];
                if(i+1 < X.size())
                    arq_out << ", ";
            }
            arq_out << "}" << endl;
            grafo->kruskal(X, arquivo_saida);
            arq_out << endl << endl;
        }

        break;

    case 'i':
        if (grafo->isDirecionado())
            std::cout << "Esse grafo é direcionado. Logo, não é possível realizar esta funcionalidade." << endl;
        else
        {
            std::cout << "Digite o ID de um vértice do grafo, entre 0 e " << grafo->getNumVertices() - 1 << ": ";
            std::cin >> id;
            while(id >= grafo->getNumVertices() || id < 0)
            {
                std::cout << "Valor de ID inválido. Por favor, tente novamente, digitando um valor entre 0 e " << grafo->getNumVertices() - 1 << ": ";
                std::cin >> id;
            }
            arq_out << "Funcionalidade i) Árvore dada pela ordem de caminhamento em profundidade:" << endl;
            arq_out << "Caminhamento a partir do vértice " << id << endl;
            grafo->caminhamentoProfundidade(id, arquivo_saida);
            arq_out << endl << endl;
        }

        break;

    default:
        std::cout << "Opção inválida. Tente novamente, digitando uma opção válida (a, b, c, d, e, f, g, h ou i): ";
        std::cin >> opc;
        funcionalidades(opc, grafo, arquivo_saida);
        break;
    }

    std::cout << endl
         << "Deseja testar outra funcionalidade? (s/n)" << endl;
    char s_n;
    std::cin >> s_n;
    testarNovamente(s_n, grafo, arquivo_saida);
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

    ofstream arq_out;
    arq_out.open(arquivo_saida, ios::out);
    if(!arq_out.is_open())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO DE SAIDA" << endl;
        exit(0);
    }

    print_menu(grafo, arquivo_saida);

    return 0;
}