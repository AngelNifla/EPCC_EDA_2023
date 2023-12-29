#ifndef _KD_TREE_H_

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

#include "Point.h"

// Definición de un punto en el espacio k-dimensional
/*struct Point {
    std::vector<double> coordinates;

    Point( std::vector<double>& coords) : coordinates(coords) {}
};*/

// Definición de un nodo en el árbol k-d
struct KDNode {
    Point point;
    KDNode* left;
    KDNode* right;

    KDNode(Point& p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
    // Constructor
    KDTree() : root(nullptr) {}

    // Función para insertar un punto en el árbol k-d
    void insert(Point& point) {
        root = insertRecursive(root, point, 0);
    }

    // Función para buscar el punto más cercano en el árbol k-d
    Point findNearestNeighbor(Point& target)  {
        double bestDistance = std::numeric_limits<double>::max();
        return findNearestNeighborRecursive(root, target, 0, bestDistance);
    }

private:
    // Función recursiva para insertar un punto en el árbol k-d
    KDNode* insertRecursive(KDNode* node, Point& point, size_t depth) {
        if (!node) {
            return new KDNode(point);
        }

        size_t k = point.getDimensions();
        size_t axis = depth % k;

        if (point.getVal(axis) < node->point.getVal(axis)) {
            node->left = insertRecursive(node->left, point, depth + 1);
        } else {
            node->right = insertRecursive(node->right, point, depth + 1);
        }

        return node;
    }

    // Función recursiva para buscar el punto más cercano en el árbol k-d
    Point findNearestNeighborRecursive(KDNode* node, Point& target, size_t depth, double& bestDistance)  {
        if (!node) {
            return Point({std::numeric_limits<double>::max(),std::numeric_limits<double>::max()}); // Punto vacío si el árbol está vacío
        }

        size_t k = target.getDimensions();
        size_t axis = depth % k;

        KDNode* nextBranch = (target.getVal(axis) < node->point.getVal(axis)) ? node->left : node->right;
        KDNode* otherBranch = (nextBranch == node->left) ? node->right : node->left;

        Point best = findNearestNeighborRecursive(nextBranch, target, depth + 1, bestDistance);

        if (distanceSquared(target, best) > distanceSquared(target, node->point)) {
            best = node->point;
            bestDistance = distanceSquared(target, best);
        }

        if (std::abs(target.getVal(axis) - node->point.getVal(axis)) < std::sqrt(bestDistance)) {
            Point candidate = findNearestNeighborRecursive(otherBranch, target, depth + 1, bestDistance);
            if (distanceSquared(target, candidate) < bestDistance) {
                best = candidate;
            }
        }

        return best;
    }

    // Función auxiliar para calcular la distancia euclidiana cuadrada entre dos puntos
    double distanceSquared(Point& p1,Point& p2)  {
        double distance = 0.0;
        for (size_t i = 0; i < p1.getDimensions(); ++i) {
            double diff = p1.getVal(i) - p2.getVal(i);
            distance += diff * diff;
        }
        
        distance = sqrt(distance);
        return distance;
    }

    KDNode* root;
};
/*
int main() {
    // Ejemplo de uso
    KDTree kdTree;

    Point A(2, 3);
    Point B(5, 4);
    Point C(9, 6);
    Point D(4, 7);
    Point E(8, 1);
    Point F(7, 2);

    // Insertar puntos en el árbol
    kdTree.insert(A);
    kdTree.insert(B);
    kdTree.insert(C);
    kdTree.insert(D);
    kdTree.insert(E);
    kdTree.insert(F);

    // Buscar el punto más cercano al punto (6, 5)
    Point target({6, 5});
    Point nearestNeighbor = kdTree.findNearestNeighbor(target);

    // Imprimir el resultado
    std::cout << "Punto más cercano a (" << target.getVal(0) << ", " << target.getVal(1) << "): ("<< nearestNeighbor.getVal(0) << ", " << nearestNeighbor.getVal(1) << ")\n";

    return 0;
}
*/

#endif