#include "Kmeans.h"
#include <chrono>

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        std::cout << "Error: command-line discrepancia en los argumentos. \n ./k <INPUT> <K> <OUT-DIR> <N>" << std::endl;
        return 1;
    }

    std::string output_dir = argv[4];

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
        
        if((pointId+1)>atoi(argv[3]))
        {
            break;
        }else
        {
            pointId++;
        }
        
    }
    
    infile.close();
    std::cout << "\nDatos obtenidos correctamente!\n\n";

    // Retornar si número de clusters > número de puntos
    if ((int)all_points.size() < K)
    {
        std::cout << "Error: Numero de clusters mayor que points." << std::endl;
        return 1;
    }

    // Ejecucion K-Means Clustering
    int iters = 100;
    std::cout<<"Numero de Datos: "<<all_points.size()<<"\n";
    std::cout<<"\n----------------VERSION 1-----------------\n";

    KMeans kmeans(K, iters, output_dir);
    auto inicio_T = std::chrono::high_resolution_clock::now();
    kmeans.run(all_points);
    auto fin_T = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin_T - inicio_T);

    std::cout<<"\n----------------VERSION 2-----------------\n";
    auto inicio_T2 = std::chrono::high_resolution_clock::now();
    kmeans.run_KD_tree(all_points);
    auto fin_T2 = std::chrono::high_resolution_clock::now();
    auto duracion2 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_T2 - inicio_T2);

    std::ofstream time2;
    time2.open(output_dir + "/" + std::to_string(K) + "-" + std::to_string(all_points.size()) +"_time.txt");
    if (time2.is_open())
    {
        std::cout <<"Fuerza Bruta: " << duracion.count() << " milisegundos\n";
        time2 << duracion.count()<<"\n";
        std::cout <<"Kd-Tree: " << duracion2.count() << " milisegundos\n";
        time2 << duracion2.count()<<"\n";
        time2.close();
    }
    else
    {
        std::cout << "Error: No se puede escribir en clusters.txt";
    }


    return 0;
}
