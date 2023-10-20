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

_Mutex class Matriz{
    private:

    double **matriz_fr;
    double **matriz_fi;
    double **matriz_wr;

    int n;

    public:

    Matriz(int n) : n(n) {
        matriz_fr = new double*[n];
        matriz_fi = new double*[n];
        matriz_wr = new double*[n];

        for(int i = 0; i < n; i++){
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

    /*double **getMatriz_fr(){
        return matriz_fr;
    }

    double **getMatriz_fi(){
        return matriz_fi;
    }

    double **getMatriz_wr(){
        return matriz_wr;
    }*/

    void setMatriz_fr(int i, int j, double peso_w, double visibilidad_real){
        matriz_fr[i][j] += (peso_w * visibilidad_real);
    } 

    void setMatriz_fi(int i, int j, double peso_w, double visibilidad_imaginaria){
        matriz_fi[i][j] += (peso_w * visibilidad_imaginaria);
    }

    void setMatriz_wr(int i, int j, double valor){
        matriz_wr[i][j] += (valor);
    }

    /*void setDividirMatrizReal(int i, int j){
        matriz_fr[i][j] = matriz_fr[i][j] / matriz_wr[i][j];
    }

    void setDividirMatrizImaginaria(int i, int j){
        matriz_fi[i][j] = matriz_fi[i][j] / matriz_wr[i][j];
    }*/

    void setNormalizarMatrices()
    {
        for (int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
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
    
    //Escribir e archivos
    void escribirArchivo (string gridding_real, string gridding_imaginario){
        FILE*  archivo_datos_grideados_r = fopen (gridding_real.c_str(), "wb");
        FILE*  archivo_datos_grideados_i = fopen (gridding_imaginario.c_str(), "wb");

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                fwrite(&matriz_fr[i][j], sizeof(double), 1, archivo_datos_grideados_r);
                fwrite(&matriz_fi[i][j], sizeof(double), 1, archivo_datos_grideados_i);
            }
        }

        cout << "Los archivos " << gridding_real << " y " << gridding_imaginario << " han sido creados" << endl;

        fclose(archivo_datos_grideados_r);
        fclose(archivo_datos_grideados_i);
    }

    ~Matriz(){
        for(int i = 0; i < n; i++){
            delete[] matriz_fr[i];
            delete[] matriz_fi[i];
            delete[] matriz_wr[i];
        }
        delete[] matriz_fr;
        delete[] matriz_fi;
        delete[] matriz_wr;
    }
};