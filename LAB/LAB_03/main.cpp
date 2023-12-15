#include "Octree.h"

int main()
{
    std::string name{"data/points2.csv"};
    std::vector<std::vector<long double>>puntos;
    io::CSVReader<4> in(name);
    in.read_header(io::ignore_extra_column,"", "x", "y", "z");
    int posicion,n{0}; 
    long double x, y, z;
    while(in.read_row(posicion, x, y, z)){
        puntos.push_back({x, y, z});
        n++;
    }

    Octree tree(-500,-500,-500,500,500,500);

    std::cout << "points2.csv -> Insertando puntos...\n\n";
    for (int i = 0; i < n; i++)
    {
        tree.insert(puntos[i][0],puntos[i][1],puntos[i][2]);
    }
    std::cout << "-> Se insertaron los Puntos de points2.csv.\n";
    
    return 0;
}