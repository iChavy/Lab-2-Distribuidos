#include "corrutina.cc"
#include "tarea.cc"
#include "tarea_local.cc"

int main(int argc, char *argv[])
{
    string nombre_archivo_entrada, nombre_datos_grideados;
    double delta_x, delta_u, delta_v;
    int n, chunk_lectura, numero_tareas, opcion;

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
            n = stoi(optarg);
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

    double **matriz_fr_local = new double *[n];
    double **matriz_fi_local = new double *[n];
    double **matriz_wr_local = new double *[n];

    for (int i = 0; i < n; i++)
    {
        matriz_fr_local[i] = new double[n];
        matriz_fi_local[i] = new double[n];
        matriz_wr_local[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            matriz_fr_local[i][j] = 0.0;
            matriz_fi_local[i][j] = 0.0;
            matriz_wr_local[i][j] = 0.0;
        }
    }

    delta_x = (M_PI * delta_x) / (3600 * 180);
    
    // Imagen I(x, y) es delta_x y delta_y, luego la distancia en los puntos de su transformada V(u, v) es:
    delta_u = 1 / (n * delta_x);
    delta_v = 1 / (n * delta_x);
    

    Lectura leer(nombre_archivo_entrada, chunk_lectura);
    Matriz matrices(n);
    Tarea **tarea = new Tarea *[numero_tareas];

    // Creación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        tarea[i] = new Tarea(&leer, i, &matrices, delta_x, delta_u, delta_v, n);
    }

    // Eliminación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        //fprintf(stderr, "Eliminando tarea %d\n", i);
        delete tarea[i];
    }
    delete[] tarea;

    // Normalización matriz
    matrices.setNormalizarMatrices();

    // Escribir en archivo las matrices
    matrices.escribirArchivo("datosgrideadosr.raw", "datosgrideadosi.raw");

    ///////////////////////////////////////////////////////////////////////////// pt 2 /////////////////////////////////////////////////////////////////////////////
    Lectura leer_local(nombre_archivo_entrada, chunk_lectura);

    Tarea_local **tarea_local = new Tarea_local *[numero_tareas];

    // Creación de tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        tarea_local[i] = new Tarea_local(&leer_local, i, delta_x, delta_u, delta_v, n);
    }

    // Sumar matrices locales de cada tarea
    for (int i = 0; i < numero_tareas; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                matriz_fr_local[j][k] += tarea_local[i]->get_matriz_fr_local()[j][k];
                matriz_fi_local[j][k] += tarea_local[i]->get_matriz_fi_local()[j][k];
                matriz_wr_local[j][k] += tarea_local[i]->get_matriz_wr_local()[j][k];
            }
        }
    }

    // eliminacion tareas
    for (int i = 0; i < numero_tareas; i++)
    {
        // fprintf(stderr, "Eliminando tarea %d\n", i);
        delete tarea_local[i];
    }

    delete[] tarea_local;

    // Normalización matriz local
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz_wr_local[i][j] == 0)
            {
                matriz_fr_local[i][j] = 0.0;
                matriz_fi_local[i][j] = 0.0;
            }
            else
            {
                matriz_fr_local[i][j] = matriz_fr_local[i][j] / matriz_wr_local[i][j];
                matriz_fi_local[i][j] = matriz_fi_local[i][j] / matriz_wr_local[i][j];
            }
        }
    }

    // escribir en archivo las matrices locales
    FILE *archivo_datos_grideados_r_local = fopen("datosgrideadosr_local.raw", "wb");
    FILE *archivo_datos_grideados_i_local = fopen("datosgrideadosi_local.raw", "wb");

    cout << "Escribiendo en archivo local..." << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fwrite(&matriz_fr_local[i][j], sizeof(double), 1, archivo_datos_grideados_r_local);
            fwrite(&matriz_fi_local[i][j], sizeof(double), 1, archivo_datos_grideados_i_local);
        }
    }

    fclose(archivo_datos_grideados_r_local);
    fclose(archivo_datos_grideados_i_local);

    // liberar memoria matriz local
    for (int i = 0; i < n; i++)
    {
        delete[] matriz_fr_local[i];
        delete[] matriz_fi_local[i];
        delete[] matriz_wr_local[i];
    }

    delete[] matriz_fr_local;
    delete[] matriz_fi_local;
    delete[] matriz_wr_local;

    return 0;
};