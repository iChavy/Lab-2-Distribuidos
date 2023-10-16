#include "corrutina.cc"
#include "tarea.cc"

// hacer codigo para que lea por linea de comando lo siguiente: -i datosuv.raw -o datosgrideados -d delta_x -N tamanoimagen -c chunklectura -t numerotareas

int main(int argc, char *argv[])
{
    string nombre_archivo_entrada, nombre_datos_grideados;
    double delta_x;
    int tamanyo_imagen, chunk_lectura, numero_tareas, opcion;

    while ((opcion = getopt(argc, argv, "i:o:d:N:c:t:")) != -1)
    {
        switch (opcion)
        {
        case 'i':
            nombre_archivo_entrada = optarg;
            break;
        case 'o':
            nombre_datos_grideados = optarg;
            break;
        case 'd':
            delta_x = stod(optarg);
            break;
        case 'N':
            tamanyo_imagen = stoi(optarg);
            break;
        case 'c':
            chunk_lectura = stoi(optarg);
            break;
        case 't':
            numero_tareas = stoi(optarg);
            break;
        default:
            cerr << "Error en la entrada de parametros" << endl;
            exit(EXIT_FAILURE);
        }
    }

    // BORRAR Y REEMPLAZAR POR EN GETOPT ????
    int n = tamanyo_imagen;
    // Crear una matriz dinámica de tipo double e inicializarla con 0.0
    double **matriz_fr = new double *[n];
    double **matriz_fi = new double *[n];
    double **matriz_wr = new double *[n];

    for (int i = 0; i < n; i++)
    {
        matriz_fr[i] = new double[n];
        matriz_fi[i] = new double[n];
        matriz_wr[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            matriz_fr[i][j] = 0.0;
            matriz_fi[i][j] = 0.0;
            matriz_wr[i][j] = 0.0;
        }
    }

    // crear todo con new<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    Lectura leer(nombre_archivo_entrada, chunk_lectura);

    Tarea **tarea = new Tarea *[numero_tareas];

    // Creación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        //fprintf(stderr, "Creando tarea %d\n", i);
        // Paso como parámetro el puntero a la lectura y el id de la tarea
        tarea[i] = new Tarea(&leer, i, matriz_fr, matriz_fi, matriz_wr, delta_x, n);
    }

    // Eliminación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        //fprintf(stderr, "Eliminando tarea %d\n", i);
        delete tarea[i];
    }

    delete[] tarea;
    
    // Normalización matriz
    for (int i = 0; i < tamanyo_imagen; i++)
    {
        for (int j = 0; j < tamanyo_imagen; j++)
        {
            if ( matriz_wr[i][j] == 0){
                matriz_fr[i][j] = 0;
                matriz_fi[i][j] = 0;
            }
            else{
                matriz_fr[i][j] = matriz_fr[i][j] / matriz_wr[i][j];
                matriz_fi[i][j] = matriz_fi[i][j] / matriz_wr[i][j];
            }
        }
    }
    
    // Escribir en archivo las matrices
    ofstream archivo_datos_grideados_r("datosgrideadosr.raw");
    ofstream archivo_datos_grideados_i("datosgrideadosi.raw");

    cout << "Escribiendo en archivo..." << endl;

    for (int i = 0; i < tamanyo_imagen; i++)
    {
        for (int j = 0; j < tamanyo_imagen; j++)
        {
            archivo_datos_grideados_r << matriz_fr[i][j] << " ";
            archivo_datos_grideados_i << matriz_fi[i][j] << " ";
        }
        archivo_datos_grideados_r << endl;
        archivo_datos_grideados_i << endl;
    }

    archivo_datos_grideados_r.close();
    archivo_datos_grideados_i.close();


    // Liberar memoria de la matriz
    for (int i = 0; i < tamanyo_imagen; i++)
    {
        delete[] matriz_fr[i];
        delete[] matriz_fi[i];
        delete[] matriz_wr[i];
    }
    delete[] matriz_fr;
    delete[] matriz_fi;
    delete[] matriz_wr;

    // Destructores
    //leer.~Lectura(); <---- preguntar


    return 0;
}