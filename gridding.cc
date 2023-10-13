#include "corutina.cc"

// hacer codigo para que lea por linea de comando lo siguiente: -i datosuv.raw -o datosgrideados -d deltau -N tamanoimagen -c chunklectura -t numerotareas

int main (int argc, char* argv[]){
    string nombre_archivo_entrada, nombre_datos_grideados;
    double deltau;
    int tamanyo_imagen, chunk_lectura, numero_tareas, opcion;

    while ((opcion = getopt(argc, argv, "i:o:d:N:c:t:")) != -1){
        switch (opcion){
            case 'i':
                nombre_archivo_entrada = optarg;
                break;
            case 'o':
                nombre_datos_grideados = optarg;
                break;
            case 'd':
                deltau = stod(optarg);
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

    Lectura leer(nombre_archivo_entrada, chunk_lectura);
    
    // Creación de tareas
    for (int i = 0; i < numero_tareas; i++){
        Tarea tarea_lectura(leer.leer_n_lineas)
    }
    
    return 0;
}