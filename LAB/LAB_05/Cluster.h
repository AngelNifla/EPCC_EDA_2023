#ifndef _CLUSTER_H_

#include "Kd_tree.h"

class Cluster
{
private:
    int Id;
    std::vector<double> centroide;
    std::vector<Point> puntos;

public:
    Cluster(int Id, Point centroide)
    {
        this->Id = Id;
        for (int i = 0; i < centroide.getDimensions(); i++)
        {
            this->centroide.push_back(centroide.getVal(i));
        }
        this->addPoint(centroide);
    }

    void addPoint(Point p)
    {
        p.setCluster(this->Id);
        puntos.push_back(p);
    }

    bool removePoint(int pointId)
    {
        int size = puntos.size();

        for (int i = 0; i < size; i++)
        {
            if (puntos[i].getID() == pointId)
            {
                puntos.erase(puntos.begin() + i);
                return true;
            }else{}
        }
        return false;
    }

    void removeAllPoints()
    {
        puntos.clear();
    }

    int getId()
    {
        return Id;
    }

    Point getPoint(int i)
    {
        return puntos[i];
    }

    int getSize()
    {
        return puntos.size();
    }

    double getCentroidByPos(int i)
    {
        return centroide[i]; 
        }

    void setCentroidByPos(int i, double valor)
    { 
        this->centroide[i] = valor;
    }
};

#endif