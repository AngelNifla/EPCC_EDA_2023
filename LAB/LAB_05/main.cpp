#include "Kmeans.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "Error: command-line discrepancia en los argumentos. \n ./k <INPUT> <K> <OUT-DIR>" << std::endl;
        return 1;
    }

    std::string output_dir = argv[3];

    // Numero de clusters
    int K = atoi(argv[2]);

    // Abrir archivo para buscar puntos
    std::string filename = argv[1];
    std::ifstream infile(filename.c_str());

    if (!infile.is_open())
    {
        std::cout << "Error: No se puede abrir el archivo." << std::endl;
        return 1;
    }

    // Obteniendo puntos del archivo
    int pointId = 1;
    std::vector<Point> all_points;
    std::string line;

    while (getline(infile, line))
    {
        Point point(pointId, line);
        all_points.push_back(point);
        pointId++;
    }
    
    infile.close();
    std::cout << "\nDatos obtenidos correctamente!" << std::endl
         << std::endl;

    // Retornar si número de clusters > número de puntos
    if ((int)all_points.size() < K)
    {
        std::cout << "Error: Numero de clusters mayor que points." << std::endl;
        return 1;
    }

    // Ejecucion K-Means Clustering
    int iters = 100;

    KMeans kmeans(K, iters, output_dir);
    kmeans.run(all_points);

    return 0;
}
