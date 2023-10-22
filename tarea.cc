#include "tarea.h"

    /*
    Descripción: Mientras el vector no esté vacío, ingresa a la corrutina de lectura, y los chunks leídos los almacena en un vector.
                 Luego, extrae los datos del vector con split y los guarda en otro vector. Después transforma las coordenadas u, v a longitud de onda, determina la posición de la matriz que corresponde la visibilidad y lo acumula en la matriz con exclusión mutua que es compartida. En el caso de que el vector esté vacío, significa que ya no hay más chunks por leer, por lo que las tareas terminan.
    Entrada: No posee entrada
    Salida: No posee salida
    */

    void Tarea::main()
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
                    //  Determina la posición de la matriz que corresponde la visibilidad
                    i_k = round((u_k / delta_u) + n / 2);
                    j_k = round((v_k / delta_v) + n / 2);

                    // Acumula en matriz
                    matrices_globales->setMatriz_fr(i_k, j_k, peso_w, visibilidad_real);
                    matrices_globales->setMatriz_fi(i_k, j_k, peso_w, visibilidad_im);
                    matrices_globales->setMatriz_wr(i_k, j_k, peso_w);
                }
            }

            else
            {
                flag = 1;
            }
        }
    }


    /*
    Descripción: Constructor de la clase Tarea.
    Entrada:    Lectura *corrutina: puntero a la corrutina de lectura
                int id_tarea: id de la tarea
                Matriz *matrices: puntero a la clase Matriz
                double delta_x: distancia entre los pixeles de la imagen I(x, y)
                double delta_u: distancia entre los puntos de la transformada V(u,v)
                double delta_v: distancia entre los puntos de la transformada V(u,v)
                int n: tamaño de la matriz
    Salida: No posee salida
    */
    Tarea::Tarea(Lectura * corrutina, int id_tarea, Matriz *matrices, double delta_x, double delta_u, double delta_v, int n)
        : id_tarea(id_tarea), n(n), delta_x(delta_x), delta_u(delta_u), delta_v(delta_v), corrutina_leer(corrutina), matrices_globales(matrices)
    {
    }

    /*
    Descripción: Destructor de la clase Tarea.
    Entrada: No posee entrada
    Salida: No posee salida
    */
    Tarea::~Tarea(){};

