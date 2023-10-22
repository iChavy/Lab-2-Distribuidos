#ifndef TAREA_H
#define TAREA_H

#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>
#include <sstream>
#include <cmath>
#include "corrutina.h"
#include "matriz.h"

#define VEL_LUZ 299792458

_Task Tarea
{
public:
    Tarea(Lectura * corrutina, int id_tarea, Matriz *matrices, double delta_x, double delta_u, double delta_v, int n);
    ~Tarea();

private:
    int id_tarea, n;
    double delta_x, delta_u, delta_v;
    vector<string> vector_lineas;
    Lectura *corrutina_leer;
    Matriz *matrices_globales;
    void main();
};

#endif
