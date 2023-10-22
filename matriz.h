#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <string>
#include <getopt.h>
#include <cmath>

using namespace std;

_Mutex class Matriz
{
public:
    Matriz(int n);
    void setMatriz_fr(int i, int j, double peso_w, double visibilidad_real);
    void setMatriz_fi(int i, int j, double peso_w, double visibilidad_imaginaria);
    void setMatriz_wr(int i, int j, double valor);
    void setNormalizarMatrices();
    void escribirArchivo(string gridding_real, string gridding_imaginario);
    ~Matriz();

private:
    double **matriz_fr;
    double **matriz_fi;
    double **matriz_wr;
    int n;
};

#endif