#include "corutina.h"

_Cormonitor lectura{

private:
    ifstream archivo;
    int chunk_lectura;
    // vector de strings que contiene los datos de la linea
    string vector_lineas[chunk_lectura];
    
    archivo.open(nombre_archivo_entrada);

    void main(){
        string linea;

        // Lee el archivo
        while (getline(archivo, linea)){
            vector_lineas.push_back(linea);
            suspend();
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


}

dentro de task pasar corrtuina que instancio en el main
corrutina.leer_n_lineas();

