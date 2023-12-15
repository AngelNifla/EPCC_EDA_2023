#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_

//#include<bits/stdc++.h>
//using namespace std;
#include <iostream>
#include <vector>

template<typename T>
class Bruteforce
{
private:
    int dim;
    int pos;
    std::vector<std::vector<T>> points;
public:
    Bruteforce(int max_size, int dim)
    {
        this->pos = 0;
        this->dim = dim;
        this->points.resize(max_size, std::vector<T>(dim));        
    }

    //Inserta un punto en el árbol
    void insert(std::vector<T> punto)
    {
        points[pos++] = punto;
    }

    //Busca un punto en el árbol
    bool search(std::vector<T> punto)
    {
        for(int i{0}; i < points.size(); i++)
        {
            if(points[i] == punto)
            {
                return true;
            }else{}
        }
        return false;
    }
};

#endif