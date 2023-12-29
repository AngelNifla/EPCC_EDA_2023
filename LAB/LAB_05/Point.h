#ifndef _POINT_H_

#include <iostream>
#include <vector>
#include <string>

class Point
{
private:
    int Id, clusterId;
    int dimensiones;
    std::vector<double> valores;

    std::vector<double> lineToVec(std::string &line)
    {
        std::vector<double> valores;
        std::string tmp = "";

        for (int i = 0; i < (int)line.length(); i++)
        {
            if ((48 <= int(line[i]) && int(line[i])  <= 57) || line[i] == '.' || line[i] == '+' || line[i] == '-' || line[i] == 'e')
            {
                tmp += line[i];
            }
            else if (tmp.length() > 0)
            {

                valores.push_back(stod(tmp));
                tmp = "";
            }else{}
        }
        if (tmp.length() > 0)
        {
            valores.push_back(stod(tmp));
            tmp = "";
        }

        return valores;
    }

public:
    Point(int id, std::string line)
    {
        Id = id;
        valores = lineToVec(line);
        dimensiones = valores.size();
        clusterId = 0;
    }
    Point(double i, double j)
    {
        Id = 0;
        valores.push_back(i);
        valores.push_back(j);
        dimensiones = valores.size();
        clusterId = 0;
    }

    int getDimensions()
    { 
        return dimensiones;
    }

    int getCluster()
    {
        return clusterId;
    }

    void setCluster(int i)
    {
        clusterId = i;
    }

    int getID()
    {
        return Id;
    }

    double getVal(int i)
    {
        return valores[i];
    }
};

#endif