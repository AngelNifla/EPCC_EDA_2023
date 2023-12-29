#include "KMeans.h"
#include <chrono>

int main()
{
    std::ifstream infile("input.txt");

    if (!infile.is_open())
    {
        std::cout << "Error: No se puede abrir el archivo." << std::endl;
        return 1;
    }

    int pointId = 1;
    std::vector<Point> All_pointssss;
    std::string line;

    while (getline(infile, line))
    {
        Point point(pointId, line);
        All_pointssss.push_back(point);
        pointId++;
        
    }
    
    infile.close();

    std::vector<int> K = {5, 15, 25, 50, 75};
    std::vector<int> N = {1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2200, 2400};
    int inicio{0};

    std::vector<Point> all_points;
    std::vector<std::ofstream> time(5);
    for (int a = 0; a < 5; a++)
    {
        time[a].open("times/k_"+std::to_string(K[a])+"_time.txt");
    }
    

    for (int w = 0; w < N.size(); w++)
    {
        // Obteniendo puntos del archivo
        

        for (int f = inicio; f < N[w]; f++)
        {
            all_points.push_back(All_pointssss[f]);
        }
        inicio=N[w];
        
        for (int y = 0; y < K.size(); y++)
        {
            std::string output_dir = "cluster-details-N-K";
            std::cout << "\nDatos obtenidos correctamente!\n\n";
            std::cout<<"\n################ Kmeans con "<<N[w]<<" datos y K = "<<K[y]<<" ################\n";
            

            // Ejecucion K-Means Clustering
            int iters = 100;
            std::cout<<"Numero de Datos: "<<all_points.size()<<"\n";
            std::cout<<"\n----------------VERSION : FUERZA BRUTA-----------------\n";

            KMeans kmeans(K[y], iters, output_dir);
            auto inicio_T = std::chrono::high_resolution_clock::now();
            kmeans.run(all_points);
            auto fin_T = std::chrono::high_resolution_clock::now();
            auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin_T - inicio_T);

            std::cout<<"\n----------------VERSION : KD-TREE-----------------\n";
            auto inicio_T2 = std::chrono::high_resolution_clock::now();
            kmeans.run_KD_tree(all_points);
            auto fin_T2 = std::chrono::high_resolution_clock::now();
            auto duracion2 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_T2 - inicio_T2);

            std::cout <<"Fuerza Bruta: " << duracion.count() << " milisegundos\n";
            time[y] << duracion.count()<<" ";
            std::cout <<"Kd-Tree: " << duracion2.count() << " milisegundos\n";
            time[y] << duracion2.count()<<"\n";
        }
    }
    for (int a = 0; a < 5; a++)
    {
        time[a].close();
    }
    
    return 0;
}