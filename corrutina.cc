#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <getopt.h>
#include <vector>
#include <uC++.h>

using namespace std;

// hacer condiciones de archivo vacio, formato de archivo invalido, etc
_Mutex _Coroutine Lectura
{
private:
    ifstream archivo;
    int chunk_lectura;
    string nombre_archivo_entrada;
    // vector de strings que contiene los datos de la linea
    vector<string> vector_lineas;

    void main()
    {
        string linea;
        int lineas_Actuales = 0;

        if (chunk_lectura <= 0)
        {
            cout << "Error: el chunk de lectura debe ser mayor a 0" << endl;
            exit(1);
        }

        // Cuando una tarea termina de leer y hacer el cálculo, vuelve a quedar disponible para hacerlo de nuevo con otras lineas
        while (true)
        {
            int count_lineas = 0;

            // Lee n chunks del archivo
            while (getline(archivo, linea))
            {
                vector_lineas.push_back(linea);
                count_lineas++;
                lineas_Actuales++;

                if (count_lineas == chunk_lectura)
                {
                    count_lineas = 0;
                    suspend();
                    vector_lineas.clear();
                }
                // cout << "lineas actuales: " << lineas_Actuales << endl;
            }
            // Si quedaban menos lineas por leer que el chunk, se suspende la tarea
            suspend();
            vector_lineas.clear();
        }
        // cerrar archivo
        archivo.close();
    }

public:
    // Constructor
    Lectura(string nombre_archivo_entrada, int chunk_lectura) : archivo(nombre_archivo_entrada.c_str()), chunk_lectura(chunk_lectura), nombre_archivo_entrada(nombre_archivo_entrada)
    {
        // comprobar si archivo abierto
    }

    // Get vector de lineas
    vector<string> get_vector_lineas()
    {
        resume();
        return vector_lineas;
    }

    // Destructor
    ~Lectura()
    {
    }

    void leer_n_lineas()
    {
        resume(); // activa el main de la corutina
    }
};

// dentro de task pasar corrtuina que instancio en el main
// corrutina.leer_n_lineas();
