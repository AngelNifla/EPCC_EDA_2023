#include <fstream>
#include <string>
#include "csv-parser/csv.h"
#include "bruteforce.h"
#include "kdtree.h"

const int ms = 1000000;

void insertionBruteforce()
{
    std::ofstream Archivo1;
    Archivo1.open("./docs/outInsertFB.txt");
    int max_cant = 3;

    int cant[3] = {1000,10000, 20000};
    std::vector<std::string> nameFiles(max_cant);
    for(int i{0}; i<max_cant; i++)
    {
        nameFiles[i] = "data/" + std::to_string(cant[i]) + ".csv";
    }

    std::vector<std::vector<long double>> puntos(ms);
    
    for(int i{0}; i<max_cant; i++)
    {
        
        io::CSVReader<4> in(nameFiles[i]);
        in.read_header(io::ignore_extra_column,"", "x", "y", "z");
        int pos,n{0}; 
        long double x, y, z;
        while(in.read_row(pos, x, y, z)){
            puntos[n] = {x, y, z};
            n++;
        }
        
        Bruteforce<long double> bf(cant[i], 3);

        //Inicio Temporizador
        auto inicio_T = std::chrono::high_resolution_clock::now();
        for(int j{0}; j<cant[i]; j++)
        {
            bf.insert(puntos[j]);
        }
        //Fin Temporizador
        auto fin_T = std::chrono::high_resolution_clock::now();

        auto duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin_T - inicio_T);
        Archivo1 << cant[i] << " " << duracion.count() << std::endl;

    }

    Archivo1.close();
}


void insertionKdTree()
{
    std::ofstream Archivo2;
    Archivo2.open("./docs/outInserKD.txt");
    int max_cant = 3;

    int cant[3] = {1000,10000, 20000};
    std::vector<std::string> nameFiles(max_cant);
    for(int i{0}; i<max_cant; i++)
    {
        nameFiles[i] = "data/" + std::to_string(cant[i]) + ".csv";
    }

    for(int i{0}; i<max_cant; i++)
    {
        std::array<long double, 3> *puntos = new std::array<long double, 3>[cant[i]];

        io::CSVReader<4> in(nameFiles[i]);
        in.read_header(io::ignore_extra_column,"", "x", "y", "z");
        int pos,n{0};
        long double x, y, z;
        while(in.read_row(pos, x, y, z))
        {
            puntos[n] = {x,y,z};
            n++;
        }

        KDTree<long double> kd;

        //Inicio Temporizador
        auto inicio_T = std::chrono::high_resolution_clock::now();
        for(int j{0}; j<cant[i]; j++)
        {
            kd.insert(puntos[j]);
        }
        //Fin Temporizador
        auto fin_T = std::chrono::high_resolution_clock::now();

        auto duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin_T - inicio_T);
        Archivo2 << cant[i] << " " << duracion.count() << std::endl;

        delete[] puntos;

    }

    Archivo2.close();
}

int main(int argc, char const *argv[])
{
    std::cout << "-> Insertando fuerza bruta ...\n";
    insertionBruteforce();

    std::cout << "-> Insertando kd-tree ...\n";
    insertionKdTree();
    return 0;
}
