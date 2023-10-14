#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <getopt.h>
#include <fstream>
#include <vector>
#include <uC++.h>


// agregar condiciones de apertura de archivo, si archivo no existe, si archivo esta vacio, si archivo no tiene el formato correcto
// agregar cond cuando el chunk es  maayor a las lineas por leer
_Task Tarea
{
private:
    int id_tarea, count_tareas = 0;
    // Ver sla posibilidad de seprar el vector por datos, ejemplo vector_u, vector_v, vector_w
    vector<string> vector_lineas;

    // Objeto de la clase Lectura
    Lectura *corrutina_leer;

    void main()
    {
        // Leer por corutina
        corrutina_leer->leer_n_lineas();

        // Guardar datos en vector
        vector_lineas = corrutina_leer->get_vector_lineas();

        // Imprimir vector y la tarea que lo imprime
        for (int i = 0; i < vector_lineas.size(); i++)
        {
            cout << "Tarea: " << id_tarea << " " << vector_lineas[i] << endl;
        }
    }

public:
    // Constructor le paso objeto corrutina
    Tarea(Lectura *corrutina, int id_tarea) : id_tarea(id_tarea), corrutina_leer(corrutina){};

    // Destructor
    ~Tarea(){};

};