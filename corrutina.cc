#include "corrutina.h"

_Mutex _Coroutine Lectura
{
private:
    ifstream archivo;
    int chunk_lectura;
    string nombre_archivo_entrada;
    // Vector que almacena las lineas leídas
    vector<string> vector_lineas;

    /*
    Descripción: Función que utilizan las tareas para leer el archivo de entrada mediante exclusión mutua, en esta se leen n chunks del archivo y se almacenan en un vector. Cuando se termina de leer el archivo, lo cierra.
    Entrada: No posee entrada.
    Salida: No posee retorno.
    */
    void main()
    {
        string linea;
        int lineas_Actuales = 0;

        if (chunk_lectura <= 0)
        {
            cout << "Error: el chunk de lectura debe ser mayor a 0" << endl;
            exit(1);
        }

        // Cuando una tarea termina de leer y hacer el cálculo, vuelve a quedar disponible para entrar otra vez a la corrutina y realiza el proceso nuevamente.
        while (true)
        {
            int count_lineas = 0;

            // Lee n chunks del archivo y los guarda en un vector
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
            }
            // Si quedaban menos lineas por leer que el número de chunks, se suspende la tarea.
            suspend();
            vector_lineas.clear();
        }
        archivo.close();
    }

public:
    /*
    Descripción: Constructor de la clase Lectura, además abre el archivo de entrada.
    Entrada: nombre_archivo_entrada: string que contiene el nombre del archivo de entrada a abrir.
             chunk_lectura: entero que indica la cantidad de lineas que se leen por vez.
    Salida: No posee retorno.
    */
    Lectura(string nombre_archivo_entrada, int chunk_lectura) : archivo(nombre_archivo_entrada.c_str()), chunk_lectura(chunk_lectura), nombre_archivo_entrada(nombre_archivo_entrada)
    {
        // comprobar si archivo abierto
    }

    /*
    Descripción: Activa el main de la corutina si es la primera vez que se llama a la función, lee n chunks del archivo, los almacena en un vector y lo retorna.
    Entrada: No posee entrada.
    Salida: vector_lineas: vector tipo string que contiene las lineas leídas del archivo.
    */
    vector<string> get_vector_lineas()
    {
        resume();
        return vector_lineas;
    }

    /*
    Descripción: Destructor de la clase Lectura, cierra el archivo de entrada.
    Entrada: No posee entrada.
    Salida: No posee retorno.
    */
    ~Lectura()
    {
    }
};
