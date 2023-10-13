#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fstream>
#include <vector>
#include <uC++.h>

#include "tarea.cc"


_Cormonitor Lectura{

private:
    ifstream archivo;
    int chunk_lectura;
    // vector de strings que contiene los datos de la linea
    vector<string> vector_lineas[chunk_lectura];
    
    archivo.open(nombre_archivo_entrada);

    void main(){
        string linea;

        int count_lineas = 0;

        // Lee el archivo
        while (getline(archivo, linea)){
            vector_lineas.push_back(linea);
            count_lineas++;

            if (count_lineas == chunk_lectura){
                count_lineas = 0;
                suspend();
            }
        }
    }


public:
    // Constructor
    lectura(string nombre_archivo_entrada, int chunk_lectura){};

    // Destructor
    ~lectura(){
        archivo.close();
    };

    void leer_n_lineas(){
        resume(); // activa el main de la corutina
    }


};

dentro de task pasar corrtuina que instancio en el main
corrutina.leer_n_lineas();

