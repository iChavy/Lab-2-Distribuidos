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
_Task Tarea
{
private:
    int id_tarea, count_tareas = 0;
    // Ver sla posibilidad de seprar el vector por datos, ejemplo vector_u, vector_v, vector_w
    vector<string> vector_lineas;

    // Objeto de la clase Lectura
    Lectura *corrutina_leer;

    double **matriz_fr;
    double **matriz_fi;
    double **matriz_wr;

    // Variables compartidas
    double delta_x;
    int n;

    void main()
    {
        stringstream input_stringstream;
        string valor_aux;
        vector <double> valores, valores_aux;

        // Valores archivo
        double delta_u, delta_v, u, v, visibilidad_real, visibilidad_im, peso_w, frec_obs, canal_espectral, u_k, v_k;

        int i_k, j_k, flag = 0;

        delta_x = (M_PI * delta_x) / (3600 * 180 );
        // Imagen I(x, y) es delta_x y delta_y, luego la distancia en los puntos de su transformada V(u, v) es:

                // dejar en constructor:

        delta_u = 1 / (n * delta_x);
        delta_v = 1 / (n * delta_x);

        int count_chunk = 0;
        
        while (flag == 0){
            //count_chunk++;
            
            // Leer por corrutina
            //corrutina_leer->leer_n_lineas();

            // Guardar datos en vector
            vector_lineas = corrutina_leer -> get_vector_lineas();
            if (vector_lineas.size() != 0){
                //cout << "Tarea: " << id_tarea << " lee: " << vector_lineas.size() << " lineas" << endl;
                valores.clear();

                //cout << "tamaño vector_lineas: " << vector_lineas.size() << endl;
                
                double a,b,c,d,e,fg,h,z;
                
                // Extrae datos del vector con split y lo guarda en un vector double
                for (int i = 0; i < vector_lineas.size(); i++)
                {
                    //cout << vector_lineas[i] << endl;
                    replace(vector_lineas[i].begin(), vector_lineas[i].end(), ',', ';');
                    replace(vector_lineas[i].begin(), vector_lineas[i].end(), '.', ',');
                    //cout << vector_lineas[i] << endl;

                    int split = sscanf(vector_lineas[i].c_str(),
                                            "%lf;%lf;%lf;%lf;%lf;%lf;%lf;%lf",
                                            &a, &b, &c, &d, &e, &fg, &h, &z);
                // cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << " e: " << e << " fg: " << fg << " h: " << h << " z: " << z << endl;
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
                    //cout << "frec_obs: " << frec_obs << " canal_espectral: " << canal_espectral << endl;
                    //cout << "delta_u: " << delta_u << " delta_v: " << delta_v << " u_k: " << u_k << " v_k: " << v_k << endl;
                    // Determina la posición de la matriz que corresponde la visibilidad (u_k, v_k)
                    i_k = round((u_k / delta_u) + n/2);
                    j_k = round((v_k / delta_v) + n/2);
                    
                    // Acumula en matriz
                    //cout <<"peso_w: " << peso_w << " visibilidad_real: " << visibilidad_real << " visibilidad_im: " << visibilidad_im << endl;
                    matriz_fr[i_k][j_k] += (peso_w * visibilidad_real);
                    matriz_fi[i_k][j_k] += (peso_w * visibilidad_im);
                    matriz_wr[i_k][j_k] += peso_w;
                    //cout << "i_k: " << i_k << " j_k: " << j_k << endl;
                }
            }

        else{
            //cout << "he leido: " << count_chunk*10 << "chunks" << endl;
            flag = 1;
        }
    }
    }

public:
    // Constructor le paso objeto corrutina
    Tarea(Lectura *corrutina, int id_tarea, double **matriz_fr, double **matriz_fi, double **matriz_wr, double delta_x, int n) : id_tarea(id_tarea), corrutina_leer(corrutina), matriz_fr(matriz_fr), matriz_fi(matriz_fi), matriz_wr(matriz_wr), delta_x(delta_x), n(n) {}

    // Destructor
    ~Tarea(){};

};

