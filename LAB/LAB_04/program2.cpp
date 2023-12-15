#include <fstream>
#include <string>
#include "csv-parser/csv.h"
#include "bruteforce.h"
#include "kdtree.h"

const int ms = 1000000;

void searchBruteforce()
{
    std::ofstream Archivo1;
    Archivo1.open("./docs/outSearchFB.txt");
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
        while(in.read_row(pos, x, y, z))
        {
            puntos[n] = {x, y, z};
            n++;
        }

        Bruteforce<long double> bf(cant[i], 3);

        for(int j=0; j<cant[i]; j++){
            bf.insert(puntos[j]);
        }
        
        //elijiendo algunos elementos para buscar
        int randPos = rand() % cant[i];
        std::vector<long double> query = puntos[cant[i]-1];

        //Inicio Temporizador
        auto inicio_T = std::chrono::high_resolution_clock::now();
        bf.search(query);
        //Fin Temporizador
        auto fin_T = std::chrono::high_resolution_clock::now();

        auto duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin_T - inicio_T);
        Archivo1 << cant[i] << " " << duracion.count() << std::endl;

    }

    Archivo1.close();
}


void searchKdTree(){
    std::ofstream Archivo2;
    Archivo2.open("./docs/outSearchKD.txt");
    int max_cant = 3;

    int cant[3] = {1000,10000, 20000};
    std::vector<std::string> nameFiles(max_cant);
    for(int i{0}; i<max_cant; i++)
    {
        nameFiles[i] = "data/" + std::to_string(cant[i]) + ".csv";
    }


    for(int i=0; i<max_cant; i++){
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
        
        for(int j{0}; j<cant[i]; j++)
        {
            kd.insert(puntos[j]);
        }
        
        //elijiendo algunos elementos para buscar
        int randPos = rand() % cant[i];
        std::array<long double,3> query = puntos[cant[i]-1];

        //Inicio Temporizador
        auto inicio_T = std::chrono::high_resolution_clock::now();
        kd.search(query);
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
    srand(time(NULL));

    std::cout << "Búsqueda de fuerza bruta ...\n";
    searchBruteforce();

    std::cout << "Búsqueda de kd-tree ...\n";
    searchKdTree();
    return 0;
}
