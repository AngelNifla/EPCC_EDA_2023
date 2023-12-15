#ifndef KDTREE_H_
#define KDTREE_H_

//#include<bits/stdc++.h>
#include <iostream>
#include <array>

template<typename T>
class KDTree
{
private:
    const int k = 3;        //en 3 dimensiones.
    struct Node     //Nodo
    {
        std::array<T, 3> point; // Para almacenar k puntos dimensionales.
        Node *left, *right;
    };

    // Método para crear un nodo del árbol K D
    struct Node* newNode(std::array<T, 3> vec)   
    {
        struct Node* aux = new Node;

        for (int i=0; i<k; i++)
        {
            aux->point[i] = vec[i];
        }

        aux->left = aux->right = NULL;
        return aux;
    }

    // Inserta un nuevo nodo y devuelve la raíz del árbol modificado
    Node *insertRec(Node *raiz, std::array<T, 3> punto, unsigned profun)
    {
        if (raiz == NULL)       // Si el arbol esta vacio
        {
            return newNode(punto);
        }else{}

        // Calcula la dimensión actual (cd) de la comparación
        unsigned cd = profun % k;

        // Compara el nuevo punto con la raíz en la dimensión actual 'cd' y decide el subárbol izquierdo o derecho
        if (punto[cd] < (raiz->point[cd]))
        {
            raiz->left = insertRec(raiz->left, punto, profun + 1);
        }
        else
        {
            raiz->right = insertRec(raiz->right, punto, profun + 1);
        }
        return raiz;
    }

    // Función para insertar un nuevo punto con el punto dado en Árbol KD y devuelve la nueva raíz.
    Node* insert(Node *raiz, std::array<T, 3> punto)
    {
        return insertRec(raiz, punto, 0);
    }

    // Método para determinar si dos puntos son iguales en un espacio K Dimensional
    bool arePointsSame(std::array<T, 3> punto1, std::array<T, 3> punto2)
    {
        // Comparando valores
        for (int i = 0; i < k; ++i)
        {
            if (punto1[i] != punto2[i])
            {
                return false;
            }else{}
        }
        return true;
    }

    // Busca un Punto representado por "point[]" en el árbol KD. El parámetro profundidad se utiliza para determinar el eje actual.
    bool searchRec(Node* raiz, std::array<T, 3> punto, unsigned profun)
    {
        if (raiz == NULL)
        {
            return false;
        }
        if (arePointsSame(raiz->point, punto))
        {
            return true;
        }
        // La dimensión actual se calcula utilizando la profundidad actual y las dimensiones totales (k)
        unsigned cd = profun % k;

        // Comparando el punto con raiz con respecto a cd (Dimensión actual)
        if (punto[cd] < raiz->point[cd])
        {
            return searchRec(raiz->left, punto, profun + 1);
        }else{

            return searchRec(raiz->right, punto, profun + 1);
        }
    }

    // Busca un punto en el árbol K D. Utiliza principalmente searchRec()
    bool search(Node* raiz, std::array<T, 3> punto)
    {
        // Pasar la profundidad actual como 0
        return searchRec(raiz, punto, 0);
    }

public:

    struct Node *root;
    KDTree()
    {
        root = NULL;
    }

    // Inserts a new point with given point
    void insert(std::array<T, 3> punto)
    {
        root = insert(root, punto);
    }

    // Searches a Point represented by "point[]" in the K D tree.
    bool search(std::array<T, 3> punto)
    {
        return search(root, punto);
    }

};

#endif