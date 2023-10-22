#include "tarea_local.h"

    /*
    Descripción: Mientras el vector no esté vacío, ingresa a la corrutina de lectura, y los chunks leídos los almacena en un vector.
                 Luego, extrae los datos del vector con split y los guarda en otro vector. Después transforma las coordenadas u, v a longitud de onda, determina la posición de la matriz que corresponde la visibilidad y lo acumula en la matriz local de la tarea. En el caso de que el vector esté vacío, significa que ya no hay más chunks por leer, por lo que las tareas terminan.
    Entrada: No posee entrada
    Salida: No posee salida
    */
    void Tarea_local::main()
    {
        string valor_aux;
        vector<double> valores;
        double valores_aux, u, v, visibilidad_real, visibilidad_im, peso_w, frec_obs, canal_espectral, u_k, v_k;
        int i_k, j_k, flag = 0;

        // Si recibe un vector vacío, significa que ya no hay más chunks por leer, por lo que las tareas terminan.
        while (flag == 0)
        {
             // Lee n chunks, guarda las lineas en un vector, lo retorna y lo guarda en vector_lineas.
            vector_lineas = corrutina_leer->get_vector_lineas();
            if (vector_lineas.size() != 0)
            {
                valores.clear();

                // Extrae datos del vector con split y lo guarda en otro vector.
                for (int i = 0; i < vector_lineas.size(); i++)
                {
                    replace(vector_lineas[i].begin(), vector_lineas[i].end(), ',', ';');
                    replace(vector_lineas[i].begin(), vector_lineas[i].end(), '.', ',');
                    
                    istringstream ss(vector_lineas[i]);
                    while (getline(ss, valor_aux, ';')) {
                        valores_aux = stod(valor_aux);
                        valores.push_back(valores_aux);
                    }
                }

                vector_lineas.clear();

                // Cálculo de la visibilidad
                for (int i = 0; i < valores.size(); i += 8)
                {
                    u = valores[i];
                    v = valores[i + 1];
                    visibilidad_real = valores[i + 3];
                    visibilidad_im = valores[i + 4];
                    peso_w = valores[i + 5];
                    frec_obs = valores[i + 6];
                    canal_espectral = valores[i + 7];

                    // Transformación de las coordenada u, v a longitud de onda
                    u_k = u * (frec_obs / VEL_LUZ);
                    v_k = v * (frec_obs / VEL_LUZ);
                    //  Determina la posición de la matriz que corresponde la visibilidad (u_k, v_k)
                    i_k = round((u_k / delta_u) + n / 2);
                    j_k = round((v_k / delta_v) + n / 2);
                    // cout << "calculo" << endl;

                    // Acumula en matriz
                    matriz_fr_local[i_k][j_k] += (peso_w * visibilidad_real);
                    matriz_fi_local[i_k][j_k] += (peso_w * visibilidad_im);
                    matriz_wr_local[i_k][j_k] += peso_w;
                }
            }

            else
            {
                flag = 1;
            }
        }
    }


    /*
    Descripción: Constructor de la clase Tarea_local. Cada tarea tiene su propia matriz donde almacena el gridding que inicialmente es 0.0
    Entrada:    Lectura * corrutina: corrutina que lee el archivo y retorna un vector con las lineas leídas
                int id_tarea: identificador de la tarea
                double delta_x: distancia entre los pixeles de la imagen I(x, y)
                double delta_u: distancia entre los puntos de la transformada V(u,v)
                double delta_v: distancia entre los puntos de la transformada V(u,v)
                int n: tamaño de la matriz
    Salida: No posee salida.
    */
    Tarea_local::Tarea_local(Lectura * corrutina, int id_tarea, double delta_x, double delta_u, double delta_v, int n) : id_tarea(id_tarea), n(n), delta_x(delta_x), delta_u(delta_u), delta_v(delta_v), corrutina_leer(corrutina)
    {
        matriz_fr_local = new double *[n];
        matriz_fi_local = new double *[n];
        matriz_wr_local = new double *[n];
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
    }

    /*
    Descripción: Retorna la matriz fr de gridding de la tarea
    Entrada: No posee entrada.
    Salida: double **matriz_fr_local: matriz de gridding de la tarea.
    */
     double **Tarea_local::get_matriz_fr_local()
    {
        return matriz_fr_local;
    }
    /*
    Descripción: Retorna la matriz fi de gridding de la tarea
    Entrada: No posee entrada.
    Salida: double **matriz_fi_local: matriz de gridding de la tarea.
    */
     double **Tarea_local::get_matriz_fi_local()
    {
        return matriz_fi_local;
    }
    /*
    Descripción: Retorna la matriz wr de gridding de la tarea
    Entrada: No posee entrada.
    Salida: double **matriz_wr_local: matriz de gridding de la tarea.
    */
     double **Tarea_local::get_matriz_wr_local()
    {
        return matriz_wr_local;
    }

    /*
    Descripción: Destructor de la clase Tarea_local. Elimina las matrices de gridding de la tarea.
    Entrada: No posee entrada.
    Salida: No posee salida.
    */
    Tarea_local::~Tarea_local()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] matriz_fr_local[i];
            delete[] matriz_fi_local[i];
            delete[] matriz_wr_local[i];
        }
        delete[] matriz_fr_local;
        delete[] matriz_fi_local;
        delete[] matriz_wr_local;
    };

