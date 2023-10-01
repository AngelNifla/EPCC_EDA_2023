#include <iostream>
#include <random>
#include <vector>
#include <fstream>

std::ofstream Archivo;

int main()      //Funcion principal.
{
    //Metodo para obtener números aleatorios.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<long int> t = {1000,5000,10000,50000,100000,1000000};
    for (int k = 0; k < 6; k++)
    {
        Archivo.open(std::to_string(t[k])+"_Datos_Aleatorios.txt",
                     std::ios::out);   //Creando txt.
        for (long int i = 0; i < t[k]; i++)      //Generando 1 millon de datos aleatorios entre 0.0 y 1.0
        {
            Archivo<<dis(gen)<<",";
        }
        Archivo.close();
    }
    return 0;
}
