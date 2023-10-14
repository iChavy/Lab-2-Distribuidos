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

    // crear todo con new<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    Lectura leer(nombre_archivo_entrada, chunk_lectura);

    Tarea **tarea = new Tarea *[numero_tareas];

    // Creación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        //fprintf(stderr, "Creando tarea %d\n", i);
        // Paso como parámetro el puntero a la lectura y el id de la tarea
        tarea[i] = new Tarea(&leer, i);
    }

    // Eliminación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        //fprintf(stderr, "Eliminando tarea %d\n", i);
        delete tarea[i];
    }

    delete[] tarea;

    // Destructores
    //leer.~Lectura(); <---- preguntar


    return 0;
}