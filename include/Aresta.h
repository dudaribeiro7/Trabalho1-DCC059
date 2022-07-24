#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

#include "No.h"

using namespace std;

class Aresta
{

private:
    No *no;    // Nó ao qual a aresta está ligada
    int peso;   // Peso da aresta

public:
    Aresta(No *_no, int _peso);
    ~Aresta();
    No *getNo();
    void setNo(No *_no);
    int getPeso();
    void setPeso(int _peso);
};

#endif