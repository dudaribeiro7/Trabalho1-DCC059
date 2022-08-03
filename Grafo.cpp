#include "Grafo.h"
#include <math.h>

#define infinito 999999999

// @brief Retorna a posição de um vértice a partir do ID
// @param _nos_grafo São os nós do grafo que se desfeja verificar o vértice específico
// @param id É a identificação do nó a ser verificado
// @param tam É o numero de vertices no vetor
// @return int - A posição do nó de ID id 
int getPosId(No **_nos_grafo, int id, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (_nos_grafo[i]->getId() == id)
            return i;
    }

    return -1;
}

// @brief Verifica se é possível existir uma aresta entre os nós.
// @brief Elimina a possibilidade de existência de self-loops e multiarestas.
// @param _nos_grafo São os nós do grafo que se desfeja verificar a existência da aresta
// @param id1 É a identificação do no 1 a ser verificado
// @param id2 É a identificação do no 2 a ser verificado
// @return TRUE (se for possível) ou FALSE (se não for possível, pois é multiaresta ou self-loop)
bool verificaAresta(No **_nos_grafo, int id1, int id2, int tam)
{
    if (id1 == id2)
        return false;

    if (!_nos_grafo[getPosId(_nos_grafo, id1, tam)]->getArestas().empty())
    {
        Aresta *aux = _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getArestas()[0];
        for (int j = 0; j < _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getGrau(); j++)
        {
            if (aux->getNo2()->getId() == id2)
                return false;

            if ((j + 1) < _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getGrau())
                aux = _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getArestas()[j + 1];
        }
        return true;
    }
    else
        return true;
}

// @brief Verifica se é possível existir um arco entre os nós.
// @brief Elimina a possibilidade de existência de self-loops e multiarcos.
// @param _nos_grafo São os nós do grafo que se desfeja verificar a existência do arco
// @param id1 É a identificação do no 1 a ser verificado
// @param id2 É a identificação do no 2 a ser verificado
// @return TRUE (se for possível) ou FALSE (se não for possível, pois é multiarco ou self-loop)
bool verificaArco(No **_nos_grafo, int id1, int id2, int tam)
{
    if (id1 == id2)
        return false;

    if (!_nos_grafo[getPosId(_nos_grafo, id1, tam)]->getArcos().empty())
    {
        Arco *aux = _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getArcos()[0];
        for (int j = 0; j < _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getGrauSaida(); j++)
        {
            if (aux->getNoDestino()->getId() == id2)
                return false;

            if (j + 1 < _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getGrauSaida())
                aux = _nos_grafo[getPosId(_nos_grafo, id1, tam)]->getArcos()[j + 1];
        }
        return true;
    }
    else
        return true;
}

// @brief Função para ler o arquivo contendo o grafo
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
void Grafo::leArquivo(string nomeArquivo)
{
    // abertura do arquivo:
    fstream arq;
    arq.open(nomeArquivo, ios::in);
    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        exit(0);
    }

    string line;
    getline(arq, line);
    // a primeira linha do arquivo é o numero de vertices do grafo:
    n_vertices = stoi(line);

    // instanciando o vetor de vetores com o numero de vertices:
    nos_grafo = new No *[n_vertices];
    // preenche os vetores de nós:
    int pesoNo;
    for (int i = 0; i < n_vertices; i++)
    {
        if (ponderadoNos)
            pesoNo = i; 
        else
            pesoNo = 1;
        nos_grafo[i] = new No(i, pesoNo);
    }

    // enquanto ainda houverem linhas a serem lidas:
    while (getline(arq, line))
    {
        // separa a linha, obtendo os nós e os pesos das arestas:
        stringstream ss(line);
        string aux;
        vector<int> vet;
        while (getline(ss, aux, ' ')) // espaços separam os nós e peso da aresta no arquivo
            vet.push_back(stoi(aux));
    
        int no1 = vet[0];
        int no2 = vet[1];
        int pesoAresta;
        if (ponderadoArestas)
            pesoAresta = vet[2];
        else
            pesoAresta = 1;

        if (direcionado)
        {
            if (verificaArco(this->nos_grafo, no1, no2, this->n_vertices))
            {
                // conecta o nó ao arco que o liga ao seu nó adjacente SUCESSOR:
                nos_grafo[no1]->adcArco(nos_grafo[no2], pesoAresta);
            }
        }
        else
        {
            if (verificaAresta(this->nos_grafo, no1, no2, this->n_vertices))
            {
                // conecta aos nós as arestas que os ligam aos seus adjacentes:
                nos_grafo[no1]->adcAresta(nos_grafo[no2], pesoAresta);
                nos_grafo[no2]->adcAresta(nos_grafo[no1], pesoAresta);
            }
        }
    }
    
    arq.close();
}

// @brief Retorna um subgrafo vértice induzido pelo conjunto de vértices passados por parâmetro.
// @param X subconjunto de vértices do grafo para achar o subgrafo vértice induzido
// @return Grafo* - o subgrafo vértice induzido
Grafo *Grafo::subgrafoVerticeInduzido(vector<int> X)
{
    // Aloca um novo vetor de ponteiros para os nós do subgrafo vertice induzido que será retornado:
    No **nos_subgrafo = new No *[X.size()];
    // Percorre o vetor que contém os IDs dos nós do subgrafo:
    for (int i = 0; i < X.size(); i++)
    {
        // Resgata o peso do nó a ser adicionado no subgrafo:
        int pesoNo = this->nos_grafo[X[i]]->getPesoNo();
        // Adiciona o nó no subgrafo:
        nos_subgrafo[i] = new No(X[i], pesoNo);
    }

    // Percorre o vetor que contém os IDs dos nós do subgrafo:
    for (int i = 0; i < X.size(); i++)
    {
        // Verifica se é direcionado ou não:
        if (this->direcionado)
        {
            // Percorre os nós sucessores aos nós contidos no vetor X:
            for (int j = 0; j < this->nos_grafo[X[i]]->getGrauSaida(); j++)
            {
                // Resgata o ID do no sucessor:
                int id_sucessor = this->nos_grafo[X[i]]->getNosSuc()[j]->getId();
                // Verifica se o nó sucessor também está contido no vetor X:
                if (searchInVector(X, id_sucessor))
                {
                    // Se estiver, resgata o peso do arco que será adicionado e verifica se é possível, no subgrafo, existir esse arco:
                    int pesoArco = this->nos_grafo[X[i]]->getArcos()[j]->getPeso();
                    if (verificaArco(nos_subgrafo, X[i], id_sucessor, X.size()))
                    {
                        nos_subgrafo[getPosId(nos_subgrafo, X[i], X.size())]->adcArco(nos_subgrafo[getPosId(nos_subgrafo, id_sucessor, X.size())], pesoArco);
                    }
                }
            }
        }
        else
        {
            // Percorre os nós adjacentes dos nós contidos no vetor X:
            for (int j = 0; j < this->nos_grafo[X[i]]->getGrau(); j++)
            {
                // Resgata o ID do nó adjacente:
                int id_adjacente = this->nos_grafo[X[i]]->getArestas()[j]->getNo2()->getId();
                // Verifica se o nó adjacente também está contido no vetor X:
                if (searchInVector(X, id_adjacente))
                {
                    // Se estiver, resgata o peso da aresta que será adicionada e verifica se é possível, no subgrafo, existir essa aresta:
                    int pesoAresta = this->nos_grafo[X[i]]->getArestas()[j]->getPeso();
                    if (verificaAresta(nos_subgrafo, X[i], id_adjacente, X.size()))
                    {
                        nos_subgrafo[getPosId(nos_subgrafo, X[i], X.size())]->adcAresta(nos_subgrafo[getPosId(nos_subgrafo, id_adjacente, X.size())], pesoAresta);
                        nos_subgrafo[getPosId(nos_subgrafo, id_adjacente, X.size())]->adcAresta(nos_subgrafo[getPosId(nos_subgrafo, X[i], X.size())], pesoAresta);
                    }
                }
            }
        }
    }

    Grafo *subgrafo = new Grafo(nos_subgrafo, X.size(), this->direcionado, this->ponderadoArestas, this->ponderadoNos);
    // subgrafo->printGrafo();
    return subgrafo;
}

// @brief Verifica se um determinado ID está presente no vetor
// @param vet É o vetor no qual se deseja buscar o ID
// @param id É o ID do nó que se deseja buscar
// @return TRUE se encontrar e FALSE caso contrário
bool Grafo::searchInVector(vector<int> vet, int id)
{
    for (int i = 0; i < vet.size(); i++)
        if (vet[i] == id)
            return true;
    return false;
}

// @brief Verifica se um determinado vértice está presente no vetor
// @param vet É o vetor no qual se deseja buscar o vertice
// @param id É o nó que se deseja buscar
// @return TRUE se encontrar e FALSE caso contrário
bool Grafo::searchNoInVector(vector<No *> vet, No *id)
{
    for (int i = 0; i < vet.size(); i++)
        if (vet[i] == id)
            return true;
    return false;
}

// @brief Construtor
// @param nomeArquivo É o nome do arquivo com as instâncias do grafo a ser lido
// @param direc Contém a opção do grafo ser direcionado (1) ou não (0)
// @param peso_aresta Contém a opção do grafo ser ponderado nas arestas (1) ou não (0)
// @param peso_nos Contém a opção do grafo ser ponderado nos vértices (1) ou não (0)
Grafo::Grafo(string nomeArquivo, int direc, int peso_aresta, int peso_nos)
{
    if (direc == 0)
        direcionado = false;
    else
        direcionado = true;

    if (peso_aresta == 0)
        ponderadoArestas = false;
    else
        ponderadoArestas = true;

    if (peso_nos == 0)
        ponderadoNos = false;
    else
        ponderadoNos = true;

    leArquivo(nomeArquivo);
}

// @brief Construtor
// @param _nos_grafo É o vetor de ponteiros dos nós do grafo
// @param _n_vertices É o número de vértices do grafo
// @param _direc Informação sobre se o grafo é direcionado ou não
// @param _pesoAresta Informação sobre se o grafo é ponderado nas arestas ou não
// @param _pesoNos Informação sobre se o grafo é ponderado nos vértices ou não
Grafo::Grafo(No **_nos_grafo, int _n_vertices, bool _direc, bool _pesoAresta, bool _pesoNos)
{
    this->nos_grafo = _nos_grafo;
    this->n_vertices = _n_vertices;
    this->direcionado = _direc;
    this->ponderadoArestas = _pesoAresta;
    this->ponderadoNos = _pesoNos;
}

// @brief Destrutor
Grafo::~Grafo()
{
    for (int i = 0; i < n_vertices; i++)
    {
        delete nos_grafo[i];
    }

    delete[] nos_grafo;
}

// @brief Imprime o grafo na tela
void Grafo::printGrafo()
{
    if (direcionado)
    {
        for (int i = 0; i < n_vertices; i++)
        {
            cout << nos_grafo[i]->getId() << " -> ";
            Arco *aux = nos_grafo[i]->getArcos()[0];
            for (int j = 0; j < nos_grafo[i]->getGrauSaida(); j++)
            {
                cout << aux->getNoDestino()->getId() << " -> ";
                if (j + 1 < nos_grafo[i]->getGrauSaida())
                    aux = nos_grafo[i]->getArcos()[j + 1];
            }
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < n_vertices; i++)
        {
            cout << nos_grafo[i]->getId() << " - ";
            Aresta *aux = nos_grafo[i]->getArestas()[0];
            for (int j = 0; j < nos_grafo[i]->getGrau(); j++)
            {
                cout << aux->getNo2()->getId() << " - ";
                if (j + 1 < nos_grafo[i]->getGrau())
                    aux = nos_grafo[i]->getArestas()[j+1];
            }

            cout << endl;
        }
    }
}

// @brief Retorna o número de vértices do grafo
// @return int
int Grafo::getNumVertices()
{
    return this->n_vertices;
}

// @brief Retorna o vetor de ponteiros para os nós do grafo
// @return No**
No **Grafo::getNosGrafo()
{
    return this->nos_grafo;
}

// @brief Retorna se o grafo é direcionado ou não
// @return bool
bool Grafo::isDirecionado()
{
    return this->direcionado;
}

// @brief Retorna se o grafo é ponderado nas arestas ou não
// @return bool
bool Grafo::isPonderadoArestas()
{
    return this->ponderadoArestas;
}

// @brief Retorna se o grafo é ponderado nos nós ou não
// @return bool
bool Grafo::isPonderadoNos()
{
    return this->ponderadoNos;
}

// @author @marianaricha
// @brief Realiza o caminhamento em profundidade a partir de um determinado vértice
// @param id um ID de vértice
// @return vector<No*> - Vetor de nós em que o nó deste id chega
vector<No *> Grafo::caminhamentoProfundidade(int id, string arquivo_saida)
{
    bool visitados[n_vertices];
    for (int i = 0; i < n_vertices; i++)
    {
        visitados[i] = false; // a posição no vetor de visitados será igual ao id do vértice
    }
   
    vector<No*> vetor;
    cP(id, visitados, &vetor, -1); //adiciona cada nó em que o vetor chega em um vetor de nós
    return vetor;
}

// @author @marianaricha
// @brief Adiciona o nó alcançado ao vetor.
// @brief Imprime a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro, destacando as arestas de retorno
// @param id um ID de vértice
void Grafo::cP(int id, bool v[],  vector<No*> *vetor, int aux)
{
    v[id] = true;
    cout << "Visitando o vértice " << id << endl;
    
    for (int j = 0; j < nos_grafo[id]->getNosAdj().size(); j++)
    { // verifica se é folha
        int w = nos_grafo[id]->getNosAdj()[j]->getId();
        if (!v[w])
        {
            cP(w, v, vetor, id); // recurssividade
            
        }
        
    }
    if(aux!=-1)
        cout << "Volta para o vértice " <<  aux << " pela aresta (" << id << "," << aux << ")" << endl;
    vetor->push_back(nos_grafo[id]); //retorna o nó que ele chegou
}

// @author @mariana_richa
// @brief Encontra o fecho transitivo direto de um nó
// @param id ID de um vértice do grafo
// @return vector<No*> - Fecho Transitivo Direto (vetor de vértices)
vector<No *> Grafo::fechoTransDir(int id)
{
    bool visitados[n_vertices];
    for (int i = 0; i < n_vertices; i++)
    {
        visitados[i] = false; // a posição no vetor de visitados será igual ao id do vértice
    }
   
    vector<No*> vetor;
    fechoaux(id, visitados, &vetor); //adiciona cada nó em que o vetor chega em um vetor de nós
    vetor.pop_back();
    return vetor; //vetor de nós em que o id chega
}

void Grafo::fechoaux(int id, bool v[],  vector<No*> *vetor)
{
    v[id] = true;
    
    for (int j = 0; j < nos_grafo[id]->getNosSuc().size(); j++)
    { // verifica se é folha
        int w = nos_grafo[id]->getNosSuc()[j]->getId();
        if (!v[w])
        {
            fechoaux(w, v, vetor); // recursividade
            
        }    
    }
    
    vetor->push_back(nos_grafo[id]); //retorna o nó que ele chegou
}

// @author @mariana_richa
// @brief Encontra o fecho transitivo indireto de um nó
// @param id ID de um vértice do grafo
// @return vector<No*> - Fecho Transitivo Indireto (vetor de vértices)
vector<No*> Grafo::fechoTransInd(int id)
{
    vector<No*> vetor;
    for (int i = 0; i < n_vertices; i++)
    {
        vector<No*> aux = fechoTransDir(i);
        if (searchNoInVector(aux, nos_grafo[id]) && i != id)
            vetor.push_back(nos_grafo[i]); // vetor de nós que contém o nó procurado em seu fecho transitivo direto
    }

    return vetor;
}

// @author @vitor-frnds
// @brief Encontra o coeficiente de agrupamento local de um vertice
// @param id ID de um vértice do grafo
// @return float - Coeficiente de agrupamento local do vértice
float Grafo::coeficienteAgrupamentoLocal(int id)
{
    if (direcionado)
    {
        No *NoAux;
        No *no = nos_grafo[id];

        Arco *arco1;

        float coef;
        float grau = no->getGrauSaida();
        float pv = 0;

        int a1 = 0; // indice para o arco 1
            arco1 = no->getArcos()[a1];

            for(int k = 0; k < no->getGrauSaida(); k++)
            {
                NoAux = arco1->getNoDestino();

                    for(int l = 0; l < NoAux->getGrauSaida(); l++)
                    {
                        vector<No *> suc = no->getNosSuc();

                        for (int i = 0; i < suc.size(); i++)
                        {
                            if (suc[i]->getId() == NoAux->getId())
                                pv++;
                        }
                    }

                a1++;
                arco1 = NoAux->getArcos()[a1];
            }

        grau = grau / 2;
        coef = float(pv / ((pow(grau, 2) - 1) / 2));

        return coef;
    }
    else
    {
        No *NoAux;
        No *no = nos_grafo[id];

        Aresta *aresta1;

        float coef;
        float grau = no->getGrau();
        float pv = 0;

        int a1 = 0; // indice para a aresta 1

            aresta1 = no->getArestas()[a1];

            for(int k = 0; k < no->getGrau(); k++)
            {
                NoAux = aresta1->getNo2();

                    for(int l = 0; l < NoAux->getGrau(); l++)
                    {
                        vector<No *> adj = no->getNosAdj();

                        for (int i = 0; i < adj.size(); i++)
                        {
                            if (adj[i]->getId() == NoAux->getId())
                                pv++;
                        }
                    }

                a1++;
                aresta1 = no->getArestas()[a1];
            }

        grau = grau / 2;
        coef = float(pv / ((pow(grau, 2) - 1) / 2));

        return coef;
    }
}

// @author @vitor-frnds
// @brief Encontra o coeficiente de agrupamento médio do grafo
// @return Coeficiente de agrupamento médio do grafo
float Grafo::coeficienteAgrupamentoMedio()
{
    int som = 0; // somatorio dos coeficientes de agrupamentos locais

    for (int i = 0; i < n_vertices; i++)
        som = som + coeficienteAgrupamentoLocal(nos_grafo[i]->getId());

    return (som / n_vertices);
}

// @author @RiUza02
// @brief Encontra o caminho mínimo entre esses dois vértices usando o algoritmo de Dijkstra
// @param inicio/destino dois IDs de vértices do grafo
void Grafo::dijkstra(int inicio, int destino, string arquivo_saida)
{
    ofstream arq_out;
    arq_out.open(arquivo_saida, ios::app);
    if(!arq_out.is_open())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO DE SAIDA" << endl;
        exit(0);
    }

    vector<int> beta;           // vetor de custos
    vector<int> fi;             // vetor de marcação
    vector<int> pi;             // vetor de antecessores (para achar a sequencia de vertices do caminho minimo)
    int w, r, flag, ehPossivel; // auxiliares

    // inicialização
    ehPossivel = 0;
    r = inicio;
    flag = 0;
    for (int i = 0; i < n_vertices; i++)
    {
        beta.push_back(infinito);
        fi.push_back(0);
        pi.push_back(0);
    }
    beta[inicio] = 0;
    fi[inicio] = 1;

    if (direcionado)
    {
        // verifica se o Nó inicial consegue chegar no Nó final
        vector<No *> nos = fechoTransDir(inicio);
        for (int i = 0; i < nos.size(); i++)
        {
            if (nos[i]->getId() == destino)
            {
                ehPossivel = 1;
            }
        }
        if (ehPossivel)
        {
            while (flag == 0)
            {
                // varre todos os adjacentes do nó da interação atual e atualiza seus custos
                w = r;
                vector<Arco *> auxAresta = nos_grafo[w]->getArcos();
                for (int i = 0; i < auxAresta.size(); i++)
                {
                    if (beta[auxAresta[i]->getNoDestino()->getId()] > beta[w] + auxAresta[i]->getPeso())
                    {
                        beta[auxAresta[i]->getNoDestino()->getId()] = beta[w] + auxAresta[i]->getPeso();
                        pi[auxAresta[i]->getNoDestino()->getId()] = w;
                    }
                }

                // pega o primeiro nó que não esta no conjunto solução
                int flagMenor = 0;
                int contador = 0;
                while ((flagMenor == 0) && (contador < n_vertices))
                {
                    if (fi[contador] != 1)
                    {
                        r = contador;
                        flagMenor = 1;
                    }
                    contador++;
                }

                // escolhe entre todos os nós do conjunto solução o menor deles
                for (int i = 0; i < n_vertices; i++)
                {
                    if (fi[i] != 1)
                    {
                        if ((beta[i] < beta[r]))
                        {
                            r = i;
                        }
                    }
                }

                // encerra a execução se possivel
                fi[r] = 1;
                if (w == destino)
                {
                    flag = 1;
                }
            }
        }
        else
        {
            cout << "nao existe caminho entre esses vertices";
            arq_out << "nao existe caminho entre esses vertices";
            return;
        }
    }
    else
    {
        while (flag == 0)
        {
            // varre todos os adjacentes do nó da interação atual e atualiza seus custos
            w = r;
            vector<Aresta *> auxAresta = nos_grafo[w]->getArestas();
            for (int i = 0; i < auxAresta.size(); i++)
            {
                if (beta[auxAresta[i]->getNo2()->getId()] > beta[w] + auxAresta[i]->getPeso())
                {
                    beta[auxAresta[i]->getNo2()->getId()] = beta[w] + auxAresta[i]->getPeso();
                    pi[auxAresta[i]->getNo2()->getId()] = w;
                }
            }

            // pega o primeiro nó que não esta no conjunto solução
            int flagMenor = 0;
            int contador = 0;
            while ((flagMenor == 0) && (contador < n_vertices))
            {
                if (fi[contador] != 1)
                {
                    r = contador;
                    flagMenor = contador;
                }
                contador++;
            }

            // escolhe entre todos os nós do conjunto solução o menor deles
            for (int i = 0; i < n_vertices; i++)
            {
                if (fi[i] != 1)
                {
                    if ((beta[i] < beta[r]))
                    {
                        r = i;
                    }
                }
            }

            // encerra a execução se possivel
            fi[r] = 1;
            if (w == destino)
            {
                flag = 1;
            }
        }
    }

    if (direcionado)
    {
        if (ehPossivel)
        {
            // organiza o menor caminho
            vector<int> solucao;
            flag = 0;
            int aux1 = destino;
            int aux2 = pi[destino];
            solucao.push_back(aux1);
            while (flag == 0)
            {
                aux1 = aux2;
                aux2 = pi[aux1];
                solucao.push_back(aux1);
                if (aux1 == inicio)
                {
                    flag = 1;
                }
            }

            // imprime a resposta
            cout << endl;
            for (int i = 0; i < solucao.size(); i++)
            {
                cout << " - " << pi[i] << " - ";
                arq_out << " - " << pi[i] << " - ";
            }
            cout << endl
                 << "custo: " << beta[destino];
            arq_out << endl
                 << "custo: " << beta[destino];
        }
    }
    else
    {
        // organiza o menor caminho
        vector<int> solucao;
        flag = 0;
        int aux1 = destino;
        int aux2 = pi[destino];
        solucao.push_back(aux1);
        while (flag == 0)
        {
            aux1 = aux2;
            aux2 = pi[aux1];
            solucao.push_back(aux1);
            if (aux1 == inicio)
            {
                flag = 1;
            }
        }

        // imprime a resposta
        cout << endl;
        for (int i = 0; i < solucao.size(); i++)
        {
            cout << " - " << pi[i] << " - ";
            arq_out << " - " << pi[i] << " - ";
        }
        cout << endl
             << "custo: " << beta[destino];
        arq_out << endl
             << "custo: " << beta[destino];
    }
    arq_out.close();
}

// @author @RiUza02
// @brief Encontra o caminho mínimo entre dois vértices usando o algoritmo de Floyd
// @param id1/id2 dois IDs de vértices do grafo
void Grafo::floyd(int inicio, int destino, string arquivo_saida)
{
    ofstream arq_out;
    arq_out.open(arquivo_saida, ios::app);
    if(!arq_out.is_open())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO DE SAIDA" << endl;
        exit(0);
    }

    int matrizAdj[n_vertices][n_vertices]; // matriz de custos
    int pi[n_vertices][n_vertices];        // matriz de antecessores (para achar a sequencia de vertices do caminho minimo)
    int ehPossivel;                        // auxiliar

    // Inicialização
    ehPossivel = 0;
    for (int i = 0; i < n_vertices; i++)
    {
        for (int j = 0; j < n_vertices; j++)
        {
            if (i == j)
            {
                matrizAdj[i][j] = 0;
            }
            else
            {
                matrizAdj[i][j] = infinito;
            }
            pi[i][j] = 0;
        }
    }

    if (direcionado)
    {
        // verifica se o Nó inicial consegue chegar no Nó final
        vector<No *> nos = fechoTransDir(inicio);
        for (int i = 0; i < nos.size(); i++)
        {
            if (nos[i]->getId() == destino)
            {
                ehPossivel = 1;
            }
        }

        if (ehPossivel)
        {
            // Inserindos os valores dos Nós imediatos
            vector<Arco *> auxArcos;
            for (int i = 0; i < n_vertices; i++)
            {
                auxArcos = nos_grafo[i]->getArcos();
                for (int j = 0; j < n_vertices; j++)
                {
                    matrizAdj[i][auxArcos[j]->getNoDestino()->getId()] = auxArcos[j]->getPeso();
                }
            }

            // preenchimento dos valores de distancias
            for (int i = 0; i < n_vertices; i++)
            {
                for (int j = 0; j < n_vertices; j++)
                {
                    for (int k = 0; k < n_vertices; k++)
                    {
                        if ((matrizAdj[j][i] != infinito) && (matrizAdj[i][k] != infinito))
                        {
                            if (matrizAdj[j][k] > (matrizAdj[j][i] + matrizAdj[i][k]))
                            {
                                matrizAdj[j][k] = matrizAdj[j][i] + matrizAdj[i][k];
                                pi[j][k] = i;
                            }
                        }
                    }
                }
            }

            // imprime a resposta
            cout << endl;
            int a = inicio;
            int b = destino;
            while (pi[a][b] != b)
            {
                cout << "-" << b << "-";
                arq_out << "-" << b << "-";
                b = pi[a][b];
            }
        }
        else
        {
            cout << "nao existe caminho entre esses vertices";
            arq_out << "nao existe caminho entre esses vertices";
            return;
        }
    }
    else
    {
        // Inserindos os valores dos Nós imediatos
        vector<Aresta *> auxAresta;
        for (int i = 0; i < n_vertices; i++)
        {
            auxAresta = nos_grafo[i]->getArestas();
            for (int j = 0; j < n_vertices; j++)
            {
                matrizAdj[i][auxAresta[j]->getNo2()->getId()] = auxAresta[j]->getPeso();
            }
        }

        // preenchimento dos valores de distancias
        for (int i = 0; i < n_vertices; i++)
        {
            for (int j = 0; j < n_vertices; j++)
            {
                for (int k = 0; k < n_vertices; k++)
                {
                    if ((matrizAdj[j][i] != infinito) && (matrizAdj[i][k] != infinito))
                    {
                        if (matrizAdj[j][k] > (matrizAdj[j][i] + matrizAdj[i][k]))
                        {
                            matrizAdj[j][k] = matrizAdj[j][i] + matrizAdj[i][k];
                            pi[j][k] = i;
                        }
                    }
                }
            }
        }

        // imprime a resposta
        cout << endl;
        int a = inicio;
        int b = destino;
        while (pi[a][b] != b)
        {
            cout << "-" << b << "-";
            arq_out << "-" << b << "-";
            b = pi[a][b];
        }
    }
    arq_out.close();
}

// @author @dudaribeiro7
// @brief Encontra a aresta de menor peso em todo o grafo
// @return Aresta* - A aresta de menor peso
Aresta *Grafo::arestaMenorPeso()
{
    int menorPeso = nos_grafo[0]->getArestas()[0]->getPeso();
    int idx_i = 0;
    int idx_j = 0;
    for (int i = 0; i < n_vertices; i++)
    {
        for (int j = 0; j < nos_grafo[i]->getGrau(); j++)
        {
            int peso = nos_grafo[i]->getArestas()[j]->getPeso();
            if (peso < menorPeso)
            {
                menorPeso = peso;
                idx_i = i;
                idx_j = j;
            }
        }
    }
    return nos_grafo[idx_i]->getArestas()[idx_j];
}

// @author @dudaribeiro7
// @brief Procura um item dentro de um vetor e retorna a sua posição nele.
// @param arr É o vetor no qual se deseja buscar a posição do item
// @param item É o item que se deseja saber a posição
// @return auto - A posição do item no vetor
auto findIndex(const vector<No *> arr, No *item)
{
    for (auto i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == item)
            return i;
    }
    return -1;
}

bool ehConexo(Grafo *grafo)
{
    vector<No*> fechoT_dir;
    for (int i = 0; i < grafo->getNumVertices(); i++)
    {
        fechoT_dir = grafo->fechoTransDir(grafo->getNosGrafo()[i]->getId());
        if(fechoT_dir.size() != grafo->getNumVertices() - 1)
            return false;
    }
    return true;
}

// @author @dudaribeiro7
// @brief Encontra uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim
// @param X um subconjunto de vértices de um grafo
void Grafo::prim(vector<int> X, string arquivo_saida)
{
    ofstream arq_out;
    arq_out.open(arquivo_saida, ios::app);
    if(!arq_out.is_open())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO DE SAIDA" << endl;
        exit(0);
    }

    Grafo *subgrafo = subgrafoVerticeInduzido(X);
    if(!ehConexo(subgrafo))
    {
        std::cout << "Não é possível gerar uma Árvore Geradora Mínima com o algoritmo de Prim para esse subgrafo, pois ele não é conexo." << endl;
        arq_out << "Não é possível gerar uma Árvore Geradora Mínima com o algoritmo de Prim para esse subgrafo, pois ele não é conexo." << endl;
        return;
    }
    vector<Aresta *> S;
    vector<No *> nos_conectados;
    vector<No *> nos_nao_conectados;
    vector<Aresta *> aux_arestas_menorPeso;
    int menorPeso;
    int peso;
    int idx = 0;

    for (int i = 0; i < subgrafo->getNumVertices(); i++)
        nos_nao_conectados.push_back(subgrafo->nos_grafo[i]);

    // Adiciona a aresta de menor peso do subgrafo no vetor de solução:
    S.push_back(subgrafo->arestaMenorPeso());

    // Adiciona os nós da aresta de menor peso do subgrafo no vetor de nós ja conectados:
    nos_conectados.push_back(subgrafo->arestaMenorPeso()->getNo1());
    nos_conectados.push_back(subgrafo->arestaMenorPeso()->getNo2());

    // Remove esses nós do vetor de nós não conectados:
    nos_nao_conectados.erase(nos_nao_conectados.begin() + findIndex(nos_nao_conectados, subgrafo->arestaMenorPeso()->getNo1()));
    nos_nao_conectados.erase(nos_nao_conectados.begin() + findIndex(nos_nao_conectados, subgrafo->arestaMenorPeso()->getNo2()));

    while (!nos_nao_conectados.empty())
    {
        // Encontra, para cada nó já conectado, a aresta de menor peso que o liga a um nó ainda não conectado, se esta aresta existir:
        for (int i = 0; i < nos_conectados.size(); i++)
        {
            for (int j = 0; j < nos_conectados[i]->getGrau(); j++)
            {
                if (searchNoInVector(nos_nao_conectados, nos_conectados[i]->getNosAdj()[j]))
                {
                    menorPeso = nos_conectados[i]->getArestas()[j]->getPeso();
                    for (int k = 0; k < nos_conectados[i]->getGrau(); k++)
                    {
                        if (searchNoInVector(nos_nao_conectados, nos_conectados[i]->getNosAdj()[k]))
                        {
                            peso = nos_conectados[i]->getArestas()[k]->getPeso();
                            idx = k;
                            if (peso < menorPeso)
                            {
                                menorPeso = peso;
                                idx = k;
                            }
                        }
                    }
                    aux_arestas_menorPeso.push_back(nos_conectados[i]->getArestas()[idx]);
                    break;
                }
            }
        }
        // Encontra, dentre as arestas de menor peso dos nós já conectados, aquela que tem o menor peso de todos:
        if (!aux_arestas_menorPeso.empty())
        {
            menorPeso = aux_arestas_menorPeso[0]->getPeso();
            idx = 0;
            for (int i = 0; i < aux_arestas_menorPeso.size(); i++)
            {
                peso = aux_arestas_menorPeso[i]->getPeso();
                if (peso < menorPeso)
                {
                    menorPeso = peso;
                    idx = i;
                }
            }

            // Adiciona a aresta de menor peso encontrada no vetor de solução:
            S.push_back(aux_arestas_menorPeso[idx]);

            // Adiciona os nós da aresta de menor peso encontrada no vetor de nós ja conectados (se eles já não estiverem no vetor):
            if (!searchNoInVector(nos_conectados, aux_arestas_menorPeso[idx]->getNo1()))
                nos_conectados.push_back(aux_arestas_menorPeso[idx]->getNo1());
            if (!searchNoInVector(nos_conectados, aux_arestas_menorPeso[idx]->getNo2()))
                nos_conectados.push_back(aux_arestas_menorPeso[idx]->getNo2());

            // Remove esses nós do vetor de nós não conectados (se eles estiverem no vetor):
            if (searchNoInVector(nos_nao_conectados, aux_arestas_menorPeso[idx]->getNo1()))
                nos_nao_conectados.erase(nos_nao_conectados.begin() + findIndex(nos_nao_conectados, aux_arestas_menorPeso[idx]->getNo1()));
            if (searchNoInVector(nos_nao_conectados, aux_arestas_menorPeso[idx]->getNo2()))
                nos_nao_conectados.erase(nos_nao_conectados.begin() + findIndex(nos_nao_conectados, aux_arestas_menorPeso[idx]->getNo2()));

            // Esvazia o vetor auxiliar de arestas de menor peso:
            aux_arestas_menorPeso.clear();
        }
    }

    cout << "O conjunto solução das arestas da Árvore Geradora Mínima é:" << endl;
    cout << "S = {";
    for (int i = 0; i < S.size(); i++)
    {
        cout << "(" << S[i]->getNo1()->getId() << ", " << S[i]->getNo2()->getId() << ")";
        if (i+1 < S.size())
            cout << " , ";
    }
    cout << "}";

    arq_out << "O conjunto solução das arestas da Árvore Geradora Mínima é:" << endl;
    arq_out << "S = {";
    for (int i = 0; i < S.size(); i++)
    {
        arq_out << "(" << S[i]->getNo1()->getId() << ", " << S[i]->getNo2()->getId() << ")";
        if (i+1 < S.size())
            arq_out << " , ";
    }
    arq_out << "}";

    arq_out.close();
}

// @author @dudaribeiro7
// @brief Função de comparação cujo critério é o peso da aresta
// @param a/b Duas arestas a serem comparadas
// @return TRUE se o peso da aresta "b" for menor do que o peso da aresta "a" ; FALSE caso contrário
bool compara(Aresta *&a, Aresta *&b)
{
    // Vai haver troca se o peso do segundo for menor que o do primeiro
    return b->getPeso() < a->getPeso();
}

// @author @dudaribeiro7
// @brief Método que troca a posição de dois elementos de um array
template <typename T>
void troca(T *a, T *b)
{
    T *tmp = a;
    a = b;
    b = tmp;
}

// @author @dudaribeiro7
// @brief Função de particionamento para o método de ordenação QUICKSORT
template <typename T>
int particionamento(T *array, int low, int high, bool (*compare)(T &, T &))
{

    T pivo = array[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (compare(array[j], pivo))
        {
            i++;
            troca(&array[i], &array[j]);
        }
    }
    troca(&array[i + 1], &array[high]);
    return i + 1;
}

// @author @dudaribeiro7
// @brief Função auxiliar do método de ordenação de arrays
template <typename T>
void quicksort_internal(T *array, int low, int high, bool (*compare)(T &, T &))
{
    if (low < high)
    {
        int middle = particionamento(array, low, high, compare);
        quicksort_internal(array, low, middle - 1, compare);
        quicksort_internal(array, middle + 1, high, compare);
    }
}

// @author @dudaribeiro7
// @brief Método de ordenação de arrays
// @return Devolve um array ordenado de acordo com o critério da função de comparação passada por parâmetro
template <typename T>
void quick_sort(T *array, int size, bool (*compare)(T &, T &))
{
    quicksort_internal<T>(array, 0, size - 1, compare);
}

// @author @dudaribeiro7
// @brief Encontra uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal
// @param X um subconjunto de vértices de um grafo
void Grafo::kruskal(vector<int> X, string arquivo_saida)
{
    ofstream arq_out;
    arq_out.open(arquivo_saida, ios::app);
    if(!arq_out.is_open())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO DE SAIDA" << endl;
        exit(0);
    }

    Grafo *subgrafo = subgrafoVerticeInduzido(X); // subgrafo vertice induzido por X
    vector<Aresta *> S;                           // vetor de arestas solução
    vector<Aresta *> arestas;                     // vetor com todas as arestas do subgrafo, ordenadas em ordem crescente de pesos
    int c = 0;                                    // número de arestas inseridas na AGM
    int c_max = subgrafo->getNumVertices() - 1;   // número máximo de arestas que podem ser inseridas na AGM

    // Adiciona todas as arestas do subgrafo no vetor arestas:
    for (int i = 0; i < subgrafo->getNumVertices(); i++)
        for (int j = 0; j < subgrafo->nos_grafo[i]->getGrau(); j++)
            arestas.push_back(subgrafo->nos_grafo[i]->getArestas()[j]);

    // Ordena o vetor arestas com o método QUICKSORT:
    int tam = arestas.size();
    Aresta **aux_arestas = arestas.data();
    quick_sort<Aresta *>(aux_arestas, tam, compara);
    arestas.clear();
    for (int i = 0; i < tam; i++)
        arestas.push_back(aux_arestas[i]);

    // Subarvores contendo cada uma um nó isolado:
    int n_subarvores = subgrafo->getNumVertices();
    vector<No *> *subarvores = new vector<No *>[n_subarvores];
    for (int i = 0; i < n_subarvores; i++)
        subarvores[i].push_back(subgrafo->nos_grafo[i]);

    // Adiciona a aresta no vetor de soluções se ela não formar ciclos com as arestas que já estão na solução:
    int i = 0;
    while ((c < c_max) && (i < tam))
    {
        No *u = arestas[i]->getNo1();
        No *v = arestas[i]->getNo2();
        bool ciclo = false;

        // Verifica se u e v estão na mesma subárvore:
        for (int j = 0; j < n_subarvores; j++)
        {
            // Procura os nós em todas as subarvores
            if (searchNoInVector(subarvores[j], u) && searchNoInVector(subarvores[j], v))
            {
                // Se u e v estiverem na mesma subárvore:
                ciclo = true;
                break;
            }
        }

        // Se u e v não estão na mesma subárvore:
        if (!ciclo)
        {
            // Adiciona a aresta na solução:
            S.push_back(arestas[i]);
            c++;

            // Une as subárvores que contém u e v:
            int idx_u, idx_v;
            for (int j = 0; j < n_subarvores; j++)
                if (searchNoInVector(subarvores[j], u))
                {
                    idx_u = j;
                    break;
                }
            for (int j = 0; j < n_subarvores; j++)
                if (searchNoInVector(subarvores[j], v))
                {
                    idx_v = j;
                    break;
                }
            for (int t = 0; t < subarvores[idx_v].size(); t++)
                subarvores[idx_u].push_back(subarvores[idx_v][t]);
            subarvores[idx_v].clear();
        }

        i++;
    }

    cout << "O conjunto solução das arestas da Árvore Geradora Mínima é:" << endl;
    cout << "S = {";
    for (int i = 0; i < S.size(); i++)
    {
        cout << "(" << S[i]->getNo1()->getId() << ", " << S[i]->getNo2()->getId() << ")";
        if (i+1 < S.size())
            cout << " , ";
    }
    cout << "}";

    arq_out << "O conjunto solução das arestas da Árvore Geradora Mínima é:" << endl;
    arq_out << "S = {";
    for (int i = 0; i < S.size(); i++)
    {
        arq_out << "(" << S[i]->getNo1()->getId() << ", " << S[i]->getNo2()->getId() << ")";
        if (i+1 < S.size())
            arq_out << " , ";
    }
    arq_out << "}";

    arq_out.close();
}