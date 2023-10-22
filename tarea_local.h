#ifndef TAREA_LOCAL_H
#define TAREA_LOCAL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <getopt.h>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

#define VEL_LUZ 299792458

_Task Tarea_local
{
private:
    int id_tarea, n;
    double delta_x, delta_u, delta_v;
    double **matriz_fr_local, **matriz_fi_local, **matriz_wr_local;
    vector<string> vector_lineas;
    Lectura *corrutina_leer;
    void main();
public:
    Tarea_local(Lectura * corrutina, int id_tarea, double delta_x, double delta_u, double delta_v, int n);
    double **get_matriz_fr_local();
    double **get_matriz_fi_local();
    double **get_matriz_wr_local();
    ~Tarea_local();
};

#endif