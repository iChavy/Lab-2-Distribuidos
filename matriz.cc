#include "matriz.h"

    /*
    Descripción: Constructor de la clase Matriz. Se encarga de inicializar las matrices de visibilidad real, imaginaria y de pesos con ceros.
    Entrada: n, tamaño de la matriz.
    Salida: No posee retornos.
    */
    Matriz::Matriz(int n) : n(n)
    {
        matriz_fr = new double *[n];
        matriz_fi = new double *[n];
        matriz_wr = new double *[n];

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
    }

    /*
    Descripción: Acumula el valor de la visibilidad real * el peso w en la matriz real.
    Entrada:    int i, fila de la matriz.
                int j, columna de la matriz.
                double peso_w, peso w que es el valor de confianza de la matriz.
                double visibilidad_real, parte real de la visibilidad.
    Salida: No posee retornos.
    */
    void Matriz::setMatriz_fr(int i, int j, double peso_w, double visibilidad_real)
    {
        matriz_fr[i][j] += (peso_w * visibilidad_real);
    }

    /*
    Descrición: Acumula el valor de la visibilidad imaginaria * el peso w en la matriz imaginaria.
    Entrada:    int i, fila de la matriz.
                int j, columna de la matriz.
                double peso_w, peso w que es el valor de confianza de la matriz.
                double visibilidad_imaginaria, parte imaginaria de la visibilidad.
    Salida: No posee retornos.
    */
    void Matriz::setMatriz_fi(int i, int j, double peso_w, double visibilidad_imaginaria)
    {
        matriz_fi[i][j] += (peso_w * visibilidad_imaginaria);
    }

    /*
    Descripción: Acumula el valor del peso w en la matriz de pesos.
    Entrada:    int i, fila de la matriz.
                int j, columna de la matriz.
                double valor, peso w que es el valor de confianza de la matriz.
    Salida: No posee retornos.
    */
    void Matriz::setMatriz_wr(int i, int j, double valor)
    {
        matriz_wr[i][j] += (valor);
    }

    /*
    Descripción: Normaliza las matrices de visibilidad real e imaginaria.
    Entrada: No posee entradas.
    Salida: No posee retornos.
    */
    void Matriz::setNormalizarMatrices()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matriz_wr[i][j] == 0)
                {
                    matriz_fr[i][j] = 0.0;
                    matriz_fi[i][j] = 0.0;
                }

                else
                {
                    matriz_fr[i][j] = matriz_fr[i][j] / matriz_wr[i][j];
                    matriz_fi[i][j] = matriz_fi[i][j] / matriz_wr[i][j];
                }
            }
        }
    }

    /*
    Descripción: Escribe los archivos de salida con los datos grideados.
    Entrada:    string gridding_real, nombre del archivo de salida de la parte real.
                string gridding_imaginario, nombre del archivo de salida de la parte imaginaria.
    Salida: No posee retornos.
    */
    void Matriz::escribirArchivo(string gridding_real, string gridding_imaginario)
    {
        FILE *archivo_datos_grideados_r = fopen(gridding_real.c_str(), "wb");
        FILE *archivo_datos_grideados_i = fopen(gridding_imaginario.c_str(), "wb");

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                fwrite(&matriz_fr[i][j], sizeof(double), 1, archivo_datos_grideados_r);
                fwrite(&matriz_fi[i][j], sizeof(double), 1, archivo_datos_grideados_i);
            }
        }

        cout << "Los archivos " << gridding_real << " y " << gridding_imaginario << " han sido creados" << endl;

        fclose(archivo_datos_grideados_r);
        fclose(archivo_datos_grideados_i);
    }

    /*
    Descripción: Destructor de la clase Matriz. Se encarga de liberar la memoria de las matrices de visibilidad real, imaginaria y de pesos.
    Entrada: No posee entradas.
    Salida: No posee retornos.
    */
    Matriz::~Matriz()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] matriz_fr[i];
            delete[] matriz_fi[i];
            delete[] matriz_wr[i];
        }
        delete[] matriz_fr;
        delete[] matriz_fi;
        delete[] matriz_wr;
    }
