#ifndef ARCO_H
#define ARCO_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "No.h"

using namespace std;

class No;
class Arco
{

private:
    No *no_destino;     // Destino do arco
    int peso;           // Peso do arco

public:
    Arco(No *_no_destino, int _peso);  
    ~Arco();
    No *getNoDestino();
    void setNoDestino(No *no);
    int getPeso();
    void setPeso(int _peso);
};


#endif