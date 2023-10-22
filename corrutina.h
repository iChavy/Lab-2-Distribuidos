#ifndef CORRUTINA_H
#define CORRUTINA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

_Mutex _Coroutine Lectura
{
public:
    Lectura(string nombre_archivo_entrada, int chunk_lectura);
    vector<string> get_vector_lineas();
    ~Lectura();

private:
    ifstream archivo;
    int chunk_lectura;
    string nombre_archivo_entrada;
    vector<string> vector_lineas;
    void main();
};

#endif