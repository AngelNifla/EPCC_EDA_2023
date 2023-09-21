#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>

std::ofstream Archivo;

double Dis_Euclidiana(const std::vector<double>& p1, const std::vector<double>& p2)     // Función para calcular la distancia euclidiana.
{
    double dis{0.0},dif{0.0};
    for (int i = 0; i < p1.size(); ++i)
    {
        dif = p1[i] - p2[i];
        dis += dif * dif;
        dif = 0.0;
    }
    return std::sqrt(dis);
}

int main()      //Funcion principal.
{
    //Metodo para obtener números aleatorios.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);


    // Dimensiones para los conjuntos de datos
    std::vector<int> Dimens = {10,50,100,500,1000,2000,5000};

    for (int d : Dimens)
    {
        std::vector<std::vector<double>> punts;
        for (int i = 0; i < 100; ++i)       //Se generan 100 numeros.
        {
            std::vector<double> punt(d);
            for (int j = 0; j < d; ++j)
            {
                punt[j] = dis(gen);
                //std::cout<<punt[j]<<" ";
            }
            punts.push_back(punt);
        }

        //Se abre o crea el archivo para escribir las distancias generadas.
        Archivo.open("Distancias_Puntos_dimension_"+std::to_string(d)+".txt",std::ios::out);   //Creando txt.

        // Se calcula las distancias
        int num_punt = punts.size();
        int num_dis = (num_punt * (num_punt - 1)) / 2;
        std::vector<double> dis(num_dis);

        int distanciaIndex = 0;
        for (int i = 0; i < num_punt; ++i)
        {
            for (int j = i+1; j < num_punt; ++j)
            {
                dis[distanciaIndex++] = Dis_Euclidiana(punts[i], punts[j]);
                Archivo<<Dis_Euclidiana(punts[i], punts[j])<<",";
            }
        }
        Archivo.close();
        std::cout << "Dimension: " << d << ", Distancias calculadas: " << num_dis << std::endl;
    }

    return 0;
}
