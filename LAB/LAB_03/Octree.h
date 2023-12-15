#ifndef _OCTREE_H_

#include <iostream>
#include <vector>
#include "csv-parser/csv.h"

#define SID 0   // parte superior izquierda delantera
#define SDD 1   // parte superior derecha delantera
#define IDD 2    // parte inferior derecha delantera
#define IID 3    // inferior izquierda delante
#define AID 4   // arriba izquierda atrás
#define SDT 5       // parte superior derecha trasera
#define IDT 6    // parte inferior derecha trasera
#define IIT 7    // parte inferior izquierda

struct Point{
    int x,y,z;

    Point() : x(-1), y(-1), z(-1) {}
    Point(int a, int b, int c) : x(a), y(b), z(c) {}
};

class Octree
{
    Point *punto;

    Point *sup_izq_del, *inf_der_tra;
    std::vector<Octree *> hijos;
    
public:
    Octree()
    {
        punto = new Point();
    }

    Octree(int _x, int _y, int _z)
    {
        punto = new Point(_x, _y, _z);
    }

    Octree(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2)
    {
        if(_x2 < _x1 || _y2 < _y1 || _z2 < _z1)
        {
            std::cout << "Puntos limite no son validos\n";
            return;
        }else{}
        punto = nullptr;
        sup_izq_del = new Point(_x1, _y1, _z1);
        inf_der_tra = new Point(_x2, _y2, _z2);
        hijos.assign(8, nullptr);
        for(int i = SID; i <= IIT; ++i)
        {
            hijos[i] = new Octree();
        }
    }

    void insert(int _x, int _y, int _z)
    {
        if (exist(_x, _y, _z)) {
            std::cout <<"("<<_x<<","<<_y<<","<<_z<<")  Punto ya existente\n";
            return;
        }
        if(_x < sup_izq_del->x || _x > inf_der_tra->x
            || _y < sup_izq_del->y || _y > inf_der_tra->y
            || _z < sup_izq_del->z || _z > inf_der_tra->z)
        {
            std::cout <<"("<<_x<<","<<_y<<","<<_z<<") Punto fuera del limite\n";
            return;
        }

        int mid_x = (sup_izq_del->x + inf_der_tra->x) >> 1;
        int mid_y = (sup_izq_del->y + inf_der_tra->y) >> 1;
        int mid_z = (sup_izq_del->z + inf_der_tra->z) >> 1;
        int posicion = -1;

        if(_x <= mid_x)
        {
            if(_y <= mid_y)
            {
                if(_z <= mid_z){posicion = SID;}
                else{posicion = AID;}
            }else
            {
                if(_z <= mid_z){posicion = IID;}
                else{posicion = IIT;}
            }
        }else
        {
            if(_y <= mid_y){
                if(_z <= mid_z){posicion = SDD;}
                else{posicion = SDT;}
            }
            else{
                if(_z <= mid_z){posicion = IDD;}
                else{posicion = IDT;}
            }
        }

        if(hijos[posicion]->punto == nullptr)
        {
            hijos[posicion]->insert(_x, _y, _z);
            return;
        }else if(hijos[posicion]->punto->x == -1)
        {
            delete hijos[posicion];
            hijos[posicion] = new Octree(_x, _y, _z);
            return;
        }else
        {
            int x_ = hijos[posicion]->punto->x;
            int y_ = hijos[posicion]->punto->y;
            int z_ = hijos[posicion]->punto->z;
            delete hijos[posicion];
            hijos[posicion] = nullptr;
            if(posicion == SID)
            {
                hijos[posicion] = new Octree(sup_izq_del->x, sup_izq_del->y, sup_izq_del->z, mid_x, mid_y, mid_z);
            }else if(posicion == SDD)
            {
                hijos[posicion] = new Octree(mid_x + 1, sup_izq_del->y, sup_izq_del->z, inf_der_tra->x, mid_y, mid_z);
            }else if(posicion == IDD)
            {
                hijos[posicion] = new Octree(mid_x + 1, mid_y + 1, sup_izq_del->z, inf_der_tra->x, inf_der_tra->y, mid_z);
            }else if(posicion == IID)
            {
                hijos[posicion] = new Octree(sup_izq_del->x, mid_y + 1, sup_izq_del->z, mid_x, inf_der_tra->y, mid_z);
            }else if(posicion == AID)
            {
                hijos[posicion] = new Octree(sup_izq_del->x, sup_izq_del->y, mid_z + 1, mid_x, mid_y, inf_der_tra->z);
            }else if(posicion == SDT)
            {
                hijos[posicion] = new Octree(mid_x + 1, sup_izq_del->y, mid_z + 1, inf_der_tra->x, mid_y, inf_der_tra->z);
            }else if(posicion == IDT)
            {
                hijos[posicion] = new Octree(mid_x + 1, mid_y + 1, mid_z + 1, inf_der_tra->x, inf_der_tra->y, inf_der_tra->z);
            }else if(posicion == IIT)
            {
                hijos[posicion] = new Octree(sup_izq_del->x, mid_y + 1, mid_z + 1, mid_x, inf_der_tra->y, inf_der_tra->z);
            }
            hijos[posicion]->insert(x_, y_, z_);
            hijos[posicion]->insert(_x, _y, _z);
        }
    }
    
    bool exist(int _x, int _y, int _z)
    {
        if(_x < sup_izq_del->x || _x > inf_der_tra->x
            || _y < sup_izq_del->y || _y > inf_der_tra->y
            || _z < sup_izq_del->z || _z > inf_der_tra->z)
        {
            return 0;
        }
        int mid_x = (sup_izq_del->x + inf_der_tra->x) >> 1;
        int mid_y = (sup_izq_del->y + inf_der_tra->y) >> 1;
        int mid_z = (sup_izq_del->z + inf_der_tra->z) >> 1;
        int posicion = -1;
        if(_x <= mid_x)
        {
            if(_y <= mid_y)
            {
                if(_z <= mid_z){posicion = SID;}
                else{posicion = AID;}
            }else
            {
                if(_z <= mid_z){posicion = IID;}
                else{posicion = IIT;}
            }
        }else
        {
            if(_y <= mid_y)
            {
                if(_z <= mid_z){posicion = SDD;}
                else{posicion = SDT;}
            }else
            {
                if(_z <= mid_z){posicion = IDD;}
                else{posicion = IDT;}
            }
        }
        if(hijos[posicion]->punto == nullptr)
        {
            return hijos[posicion]->exist(_x, _y, _z);
        }else if(hijos[posicion]->punto->x == -1)
        {
            return 0;
        }else
        {
            if(_x == hijos[posicion]->punto->x && _y == hijos[posicion]->punto->y && _z == hijos[posicion]->punto->z)
            {
                return 1;
            }else{}
        }
        return 0;
    }
};

#endif