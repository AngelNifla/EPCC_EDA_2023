#ifndef _KMEANS_H_

#include "Cluster.h"

#include <omp.h>
#include <algorithm>
#include <cmath>
#include <fstream>

class KMeans
{
private:
    int K, iteraciones, dimensiones, total_puntos;
    std::vector<Cluster> clusters;
    std::string output_dir;

    void clearClusters()
    {
        for (int i = 0; i < K; i++)
        {
            clusters[i].removeAllPoints();
        }
    }

    int getNearestClusterId(Point point)
    {
        double sum = 0.0, min_dist;
        int NearestClusterId;
        if(dimensiones==1) {
            min_dist = abs(clusters[0].getCentroidByPos(0) - point.getVal(0));
        }	
        else 
        {
          for (int i = 0; i < dimensiones; i++)
          {
             sum += pow(clusters[0].getCentroidByPos(i) - point.getVal(i), 2.0);
          }
          min_dist = sqrt(sum);
        }
        NearestClusterId = clusters[0].getId();

        for (int i = 1; i < K; i++)
        {
            double dist;
            sum = 0.0;
            
            if(dimensiones==1) {
                  dist = abs(clusters[i].getCentroidByPos(0) - point.getVal(0));
            } 
            else {
              for (int j = 0; j < dimensiones; j++)
              {
                  sum += pow(clusters[i].getCentroidByPos(j) - point.getVal(j), 2.0);
              }

              dist = sqrt(sum);
            }
            if (dist < min_dist)
            {
                min_dist = dist;
                NearestClusterId = clusters[i].getId();
            }else{}
        }

        return NearestClusterId;
    }

public:
    KMeans(int K, int iterations, std::string output_dir)
    {
        this->K = K;
        this->iteraciones = iterations;
        this->output_dir = output_dir;
    }
    
    void run(std::vector<Point> &all_points)
    {
        total_puntos = all_points.size();
        dimensiones = all_points[0].getDimensions();

        // Inicializando.
        std::vector<int> used_pointIds;

        for (int i = 1; i <= K; i++)
        {
            while (true)
            {
                int index = rand() % total_puntos;

                if (find(used_pointIds.begin(), used_pointIds.end(), index) ==
                    used_pointIds.end())
                {
                    used_pointIds.push_back(index);
                    all_points[index].setCluster(i);
                    Cluster cluster(i, all_points[index]);
                    clusters.push_back(cluster);
                    break;
                }else{}
            }
        }
        std::cout << "Clusters Inicializados : " << clusters.size() << "\n\n";

        std::cout << "Ejecutando K-Means Clustering...\n";

        int iter = 1;
        while (true)
        {
            std::cout << "Iteracion / de : " << iter << "/" << iteraciones << "\n";
            bool done = true;

            // Agregando todos los puntos al grupo mas cercano.
            //#pragma omp parallel for reduction(&&: done) num_threads(16)
            for (int i = 0; i < total_puntos; i++)
            {
                int currentClusterId = all_points[i].getCluster();
                int nearestClusterId = getNearestClusterId(all_points[i]);

                if (currentClusterId != nearestClusterId)
                {
                    all_points[i].setCluster(nearestClusterId);
                    done = false;
                }else{}
            }
            clearClusters();

            for (int i = 0; i < total_puntos; i++)
            {
                clusters[all_points[i].getCluster() - 1].addPoint(all_points[i]);
            }

            // Actualizando los Centroides.
            for (int i = 0; i < K; i++)
            {
                int ClusterSize = clusters[i].getSize();

                for (int j = 0; j < dimensiones; j++)
                {
                    double sum = 0.0;
                    if (ClusterSize > 0)
                    {
                        //#pragma omp parallel for reduction(+: sum) num_threads(16)
                        for (int p = 0; p < ClusterSize; p++)
                        {
                            sum += clusters[i].getPoint(p).getVal(j);
                        }
                        clusters[i].setCentroidByPos(j, sum / ClusterSize);
                    }else{}
                }
            }

            if (done || iter >= iteraciones)
            {
                std::cout << "Iteraciones de Clustering Completada con : " << iter << "\n\n";
                break;
            }else{}
            iter++;
        }

        std::ofstream pointsFile;
        pointsFile.open(output_dir + "/" + std::to_string(K) + "-" + std::to_string(total_puntos) +"points.txt", std::ios::out);

        for (int i = 0; i < total_puntos; i++)
        {
            pointsFile << all_points[i].getCluster() << std::endl;
        }

        pointsFile.close();

        std::ofstream outfile;
        outfile.open(output_dir + "/" + std::to_string(K) + "-" + std::to_string(total_puntos) +"clusters.txt");
        if (outfile.is_open())
        {
            for (int i = 0; i < K; i++)
            {
                std::cout << "Cluster " << clusters[i].getId() << " centroide : ";
                for (int j = 0; j < dimensiones; j++)
                {
                    std::cout << clusters[i].getCentroidByPos(j) << " ";
                    outfile << clusters[i].getCentroidByPos(j) << " ";
                }
                std::cout << std::endl;
                outfile << std::endl;
            }
            outfile.close();
        }
        else
        {
            std::cout << "Error: No se puede escribir en clusters.txt";
        }
    }

    void run_KD_tree(std::vector<Point> &all_points)
    {
        total_puntos = all_points.size();
        dimensiones = all_points[0].getDimensions();

        // Inicializando.
        std::vector<int> used_pointIds;
        KDTree* TREE;
        TREE = new KDTree;

        for (int i = 1; i <= K; i++)
        {
            while (true)
            {
                int index = rand() % total_puntos;

                if (find(used_pointIds.begin(), used_pointIds.end(), index) ==
                    used_pointIds.end())
                {
                    used_pointIds.push_back(index);
                    all_points[index].setCluster(i);
                    Cluster cluster(i, all_points[index]);
                    clusters.push_back(cluster);
                    Point aux=all_points[index];
                    TREE->insert(aux);
                    break;
                }else{}
            }
        }
        std::cout << "Clusters Inicializados : " << clusters.size() << "\n\n";

        std::cout << "Ejecutando K-Means Clustering...\n";

        int iter = 1;
        while (true)
        {
            std::cout << "Iteracion / de : " << iter << "/" << iteraciones << "\n";
            bool done = true;

            // Agregando todos los puntos al grupo mas cercano.
            #pragma omp parallel for reduction(&&: done) num_threads(16)
            for (int i = 0; i < total_puntos; i++)
            {
                int currentClusterId = all_points[i].getCluster();
                int nearestClusterId = getNearestClusterId(all_points[i]);
                int nearestClusterIds = TREE->findNearestNeighbor(all_points[i]).getCluster();

                if (currentClusterId != nearestClusterId)
                {
                    all_points[i].setCluster(nearestClusterId);
                    done = false;
                }else{}
            }
            clearClusters();

            for (int i = 0; i < total_puntos; i++)
            {
                clusters[all_points[i].getCluster() - 1].addPoint(all_points[i]);
            }

            // Actualizando los Centroides.
            //delete TREE;
            //KDTree* TREE;
            //TREE = new KDTree;

            for (int i = 0; i < K; i++)
            {
                int ClusterSize = clusters[i].getSize();

                for (int j = 0; j < dimensiones; j++)
                {
                    double sum = 0.0;
                    if (ClusterSize > 0)
                    {
                        #pragma omp parallel for reduction(+: sum) num_threads(16)
                        for (int p = 0; p < ClusterSize; p++)
                        {
                            sum += clusters[i].getPoint(p).getVal(j);
                        }
                        clusters[i].setCentroidByPos(j, sum / ClusterSize);
                    }else{}
                }
                Point aux(clusters[i].getCentroidByPos(0),clusters[i].getCentroidByPos(1));
                TREE->insert(aux);
            }

            if (done || iter >= iteraciones)
            {
                std::cout << "Iteraciones de Clustering Completada con : " << iter << "\n\n";
                break;
            }else{}
            iter++;
        }

        std::ofstream pointsFile;
        pointsFile.open(output_dir + "/" + std::to_string(K) + "-" + std::to_string(total_puntos) +"_kd_tree_points.txt", std::ios::out);

        for (int i = 0; i < total_puntos; i++)
        {
            pointsFile << all_points[i].getCluster() << std::endl;
        }

        pointsFile.close();

        std::ofstream outfile;
        outfile.open(output_dir + "/" + std::to_string(K) + "-" + std::to_string(total_puntos) +"_kd_tree_clusters.txt");
        if (outfile.is_open())
        {
            for (int i = 0; i < K; i++)
            {
                std::cout << "Cluster " << clusters[i].getId() << " centroide : ";
                for (int j = 0; j < dimensiones; j++)
                {
                    std::cout << clusters[i].getCentroidByPos(j) << " ";
                    outfile << clusters[i].getCentroidByPos(j) << " ";
                }
                std::cout << std::endl;
                outfile << std::endl;
            }
            outfile.close();
        }
        else
        {
            std::cout << "Error: No se puede escribir en clusters.txt";
        }
    }
};

#endif