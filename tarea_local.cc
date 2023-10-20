#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <getopt.h>
#include <vector>
#include <sstream>
#include <uC++.h>
#include <cmath>

using namespace std;

#define VEL_LUZ 299792458

// agregar condiciones de apertura de archivo, si archivo no existe, si archivo esta vacio, si archivo no tiene el formato correcto
// agregar cond cuando el chunk es  maayor a las lineas por leer
_Task Tarea_local
{
private:
    int id_tarea, n;
    double delta_x, delta_u, delta_v;
    double **matriz_fr_local, **matriz_fi_local, **matriz_wr_local;

    vector<string> vector_lineas;

    Lectura *corrutina_leer;

    void main()
    {
        double a, b, c, d, e, fg, h, z; ////////////////////////////// cambiar cuando cambie el split //////////////////////////////
        stringstream input_stringstream;
        string valor_aux;
        vector<double> valores, valores_aux;

        // Valores archivo
        double u, v, visibilidad_real, visibilidad_im, peso_w, frec_obs, canal_espectral, u_k, v_k;
        int i_k, j_k, flag = 0;

        while (flag == 0)
        {
            // Lee n chunks, guarda las lineas en un vector y lo retorna
            vector_lineas = corrutina_leer->get_vector_lineas();
            if (vector_lineas.size() != 0)
            {
                valores.clear();

                // Extrae datos del vector con split y lo guarda en un vector double
                for (int i = 0; i < vector_lineas.size(); i++)
                {
                    replace(vector_lineas[i].begin(), vector_lineas[i].end(), ',', ';');
                    replace(vector_lineas[i].begin(), vector_lineas[i].end(), '.', ',');
                    /////////////////////////////////////// cambiar split ///////////////////////////////////////

                    int split = sscanf(vector_lineas[i].c_str(),
                                       "%lf;%lf;%lf;%lf;%lf;%lf;%lf;%lf",
                                       &a, &b, &c, &d, &e, &fg, &h, &z);
                    valores.push_back(a);
                    valores.push_back(b);
                    valores.push_back(c);
                    valores.push_back(d);
                    valores.push_back(e);
                    valores.push_back(fg);
                    valores.push_back(h);
                    valores.push_back(z);
                }

                vector_lineas.clear();

                // Calculo
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

public:
    Tarea_local(Lectura * corrutina, int id_tarea, double delta_x, double delta_u, double delta_v, int n) : id_tarea(id_tarea), n(n), delta_x(delta_x), delta_u(delta_u), delta_v(delta_v), corrutina_leer(corrutina)
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

    double **get_matriz_fr_local()
    {
        return matriz_fr_local;
    }

    double **get_matriz_fi_local()
    {
        return matriz_fi_local;
    }

    double **get_matriz_wr_local()
    {
        return matriz_wr_local;
    }

    // Destructor
    ~Tarea_local()
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
};
