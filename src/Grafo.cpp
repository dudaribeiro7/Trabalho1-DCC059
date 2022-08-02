#include "Grafo.h"

#define infinito 999999999

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
        return;
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
            pesoNo = i; // qual é o peso do nó????
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
        int cont = 0;
        vector<int> vet;
        while (getline(ss, aux, ' ')) // espaços separam os nós e peso da aresta no arquivo
        {
            vet[cont] = stoi(aux);
            cont++;
        }
        int no1 = vet[0];
        int no2 = vet[1];
        int pesoAresta;
        if (ponderadoArestas)
            pesoAresta = vet[2];
        else
            pesoAresta = 1;

        if (direcionado)
        {
            if (verificaArco(this->nos_grafo, no1, no2))
            {
                // conecta o nó ao arco que o liga ao seu nó adjacente SUCESSOR:
                nos_grafo[no1]->adcArco(nos_grafo[no2], pesoAresta);
            }
        }
        else
        {
            if (verificaAresta(this->nos_grafo, no1, no2))
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
        nos_subgrafo[i] = new No(this->nos_grafo[X[i]]->getId(), pesoNo);

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
                    if (verificaArco(nos_subgrafo, i, id_sucessor))
                    {
                        nos_subgrafo[i]->adcArco(nos_subgrafo[id_sucessor], pesoArco);
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
                int id_adjacente = this->nos_grafo[X[i]]->getNosAdj()[j]->getId();
                // Verifica se o nó adjacente também está contido no vetor X:
                if (searchInVector(X, id_adjacente))
                {
                    // Se estiver, resgata o peso da aresta que será adicionada e verifica se é possível, no subgrafo, existir essa aresta:
                    int pesoAresta = this->nos_grafo[X[i]]->getArestas()[j]->getPeso();
                    if (verificaAresta(nos_subgrafo, i, id_adjacente))
                    {
                        nos_subgrafo[i]->adcAresta(nos_subgrafo[id_adjacente], pesoAresta);
                        nos_subgrafo[id_adjacente]->adcAresta(nos_subgrafo[i], pesoAresta);
                    }
                }
            }
        }
    }

    Grafo *subgrafo = new Grafo(nos_subgrafo, X.size(), this->direcionado, this->ponderadoArestas, this->ponderadoNos);
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
                    aux = nos_grafo[i]->getArestas()[j];
            }

            cout << endl;
        }
    }
}

// @author @vitor-frnds
// @brief Retorna um vértice a partir do ID
// @param _nos_grafo São os nós do grafo que se desfeja verificar o vértice específico
// @param id É a identificação do nó a ser verificado
// @return No* - O nó caso seja encontrado ou nullptr caso contrário
No *Grafo::getNoInVector(No **_nos_grafo, int id)
{
    for (int i = 0; i < n_vertices; i++)
    {
        if (_nos_grafo[i]->getId() == id)
            return _nos_grafo[i];
    }

    return nullptr;
}

// @brief Verifica se é possível existir uma aresta entre os nós.
// @brief Elimina a possibilidade de existência de self-loops e multiarestas.
// @param _nos_grafo São os nós do grafo que se desfeja verificar a existência da aresta
// @param id1 É a identificação do no 1 a ser verificado
// @param id2 É a identificação do no 2 a ser verificado
// @return TRUE (se for possível) ou FALSE (se não for possível, pois é multiaresta ou self-loop)
bool Grafo::verificaAresta(No **_nos_grafo, int id1, int id2)
{
    if (id1 == id2)
        return false;

    if (!_nos_grafo[id1]->getArestas().empty())
    {
        Aresta *aux = _nos_grafo[id1]->getArestas()[0];
        for (int j = 0; j < _nos_grafo[id1]->getGrau(); j++)
        {
            if (aux->getNo2()->getId() == id2)
                return false;

            if (j + 1 < _nos_grafo[id1]->getGrau())
                aux = _nos_grafo[id1]->getArestas()[j + 1];
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
bool Grafo::verificaArco(No **_nos_grafo, int id1, int id2)
{
    if (id1 == id2)
        return false;

    if (!_nos_grafo[id1]->getArcos().empty())
    {
        Arco *aux = _nos_grafo[id1]->getArcos()[0];
        for (int j = 0; j < _nos_grafo[id1]->getGrauSaida(); j++)
        {
            if (aux->getNoDestino()->getId() == id2)
                return false;

            if (j + 1 < _nos_grafo[id1]->getGrauSaida())
                aux = _nos_grafo[id1]->getArcos()[j + 1];
        }
        return true;
    }
    else
        return true;
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
vector<No*> Grafo::caminhamentoProfundidade(int id)
{
    bool visitados[n_vertices];
    for (int i = 0; i < n_vertices; i++)
    {
        visitados[i] = false; // a posição no vetor de visitados será igual ao id do vértice
    }
    // for(int i=id; i<n_vertices; i++){
    //     if(visitados[i]==false)
    //         cP(i, visitados);
    // }
    vector<No*> vetor;
    cP(id, visitados, vetor); //adiciona cada nó em que o vetor chega em um vetor de nós
    return vetor;
}

// @author @marianaricha
// @brief Adiciona o nó alcançado ao vetor.
// @brief Imprime a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro, destacando as arestas de retorno
// @param id um ID de vértice
void Grafo::cP(int id, bool v[],  vector<No*> vetor)
{
    v[id] = true;
    cout << "Visitando o vértice " << id << endl;

    for (int j = 0; j < nos_grafo[id]->getNosAdj().size(); j++)
    { // verifica se é folha
        int w = nos_grafo[id]->getNosAdj()[j]->getId();
        if (!v[w])
        {
            cP(w, v, vetor); //recurssividade
        }
        cout << "Volta para o vértice " << id << " pela aresta (" << id << "," << j << ")" << endl;
    }
    vetor.push_back(nos_grafo[id]); //retorna o nó que ele chegou
}

// @author @mariana_richa
// @brief Encontra o fecho transitivo direto de um nó
// @param id ID de um vértice do grafo
// @return vector<No*> - Fecho Transitivo Direto (vetor de vértices)
vector<No*> Grafo::fechoTransDir(int id)
{
    return caminhamentoProfundidade(id); //vetor de nós que o nó chega até
}

// @author @mariana_richa
// @brief Encontra o fecho transitivo indireto de um nó
// @param id ID de um vértice do grafo
// @return vector<No*> - Fecho Transitivo Indireto (vetor de vértices)
vector<No*> Grafo::fechoTransInd(int id)
{
    vector<No*> vetor;
    for(int i=0; i<n_vertices; i++){
        vector<No*> aux = caminhamentoProfundidade(i);
        if(searchNoInVector(aux, nos_grafo[id]) && i!=id)
            vetor.push_back(nos_grafo[i]); //vetor de nós que contém o nó procurado em seu fecho transitivo direto

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
        No *NoAux = nullptr;
        No *no = this->getNoInVector(nos_grafo, id);

        Arco *arco1 = nullptr;
        Arco *arco2 = nullptr;

        float coef;
        float grau = no->getGrau();
        float pv = 0;
        int proxId;

        int a1 = 0; // indice para o arco 1
        int a2 = 0; // indice para o arco 2

        if (no != nullptr)
        {
            arco1 = no->getArcos()[a1];

            while (arco1 != nullptr)
            {
                proxId = arco1->getNoDestino()->getId();
                NoAux = arco1->getNoDestino();

                if (NoAux != nullptr)
                {
                    arco2 = NoAux->getArcos()[0];

                    while (arco2 != nullptr)
                    {
                        vector<No *> suc = no->getNosSuc();

                        for (int i = 0; i < suc.size(); i++)
                        {
                            if (suc[i]->getId() == NoAux->getId())
                            {
                                pv++;
                                break;
                            }
                        }

                        a2++;
                        arco2 = NoAux->getArcos()[a2];
                    }
                }

                a1++;
                arco1 = NoAux->getArcos()[a1];
            }
        }
        
        coef = float(pv / ((pow(grau, 2) - 1) / 2));

        return coef;
    }
    else
    {
        No *NoAux = nullptr;
        No *no = this->getNoInVector(nos_grafo, id);

        Aresta *aresta1 = nullptr;
        Aresta *aresta2 = nullptr;

        float coef;
        float grau = no->getGrau();
        float pv = 0;
        int proxId;

        int a1 = 0; // indice para a aresta 1
        int a2 = 0; // indice para a aresta 2

        if (no != nullptr)
        {
            aresta1 = no->getArestas()[a1];

            while (aresta1 != nullptr)
            {
                proxId = aresta1->getNo2()->getId();
                NoAux = aresta1->getNo2();

                if (NoAux != nullptr)
                {
                    aresta2 = NoAux->getArestas()[0];

                    while (aresta2 != nullptr)
                    {
                        vector<No *> adj = no->getNosAdj();

                        for (int i = 0; i < adj.size(); i++)
                        {
                            if (adj[i]->getId() == NoAux->getId())
                            {
                                pv++;
                                break;
                            }
                        }

                        a2++;
                        aresta2 = NoAux->getArestas()[a2];
                    }
                }

                a1++;
                aresta1 = no->getArestas()[a1];
            }
        }

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
        som = som + coeficienteAgrupamentoLocal(i);

    return (som / n_vertices);
}

// @author @RiUza02
// @brief Encontra o caminho mínimo entre esses dois vértices usando o algoritmo de Dijkstra
// @param inicio/destino dois IDs de vértices do grafo
void Grafo::dijkstra(int inicio, int destino)
{
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
        vector<No*> nos = fechoTransDir(inicio);
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
            }
            cout << endl
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
        }
        cout << endl
             << "custo: " << beta[destino];
    }
}

// @author @RiUza02
// @brief Encontra o caminho mínimo entre dois vértices usando o algoritmo de Floyd
// @param id1/id2 dois IDs de vértices do grafo
void Grafo::floyd(int inicio, int destino)
{
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
        vector<No*> nos = fechoTransDir(inicio);
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
            vector<Arco *> auxAresta;
            for (int i = 0; i < n_vertices; i++)
            {
                auxAresta = nos_grafo[i]->getArcos();
                for (int j = 0; j < n_vertices; j++)
                {
                    matrizAdj[i][auxAresta[j]->getNoDestino()->getId()] = auxAresta[j]->getPeso();
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
            floydAux(inicio, destino, pi);
        }
        else
        {
            cout << "nao existe caminho entre esses vertices";
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
        floydAux(inicio, destino, pi);
    }
}

// TODO: @RiUza02
// 1- fazer o comentario que explica essa função
// 2- corrigir o erro em P[][]
void Grafo::floydAux(int a, int b, int P[][])
{
    if (P[a][b] == b)
    {
        cout << b << " ";
        return;
    }
    floydAux(a, P[a][b], P);
    cout << b << " ";
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
auto findIndex(const vector<No*> arr, No *item)
{
    for (auto i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == item)
            return i;
    }
}

// @author @dudaribeiro7
// @brief Encontra uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim
// @param X um subconjunto de vértices de um grafo
void Grafo::prim(vector<int> X)
{
    Grafo *subgrafo = subgrafoVerticeInduzido(X);
    vector<Aresta *> S;
    vector<No *> nos_conectados;
    vector<No *> nos_nao_conectados;
    vector<Aresta *> aux_arestas_menorPeso;
    int menorPeso;
    int peso;
    int idx;

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
    cout << "S = { ";
    for (int i = 0; i < S.size(); i++)
        cout << "(" << S[i]->getNo1()->getId() << ", " << S[i]->getNo2()->getId() << "), ";
    cout << " }";
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
void Grafo::kruskal(vector<int> X)
{
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
    cout << "S = { ";
    for (int i = 0; i < S.size(); i++)
        cout << "(" << S[i]->getNo1()->getId() << ", " << S[i]->getNo2()->getId() << "), ";
    cout << " }";
}

