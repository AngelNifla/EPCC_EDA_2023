#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

// Definición de un punto en el espacio k-dimensional
struct Point {
    std::vector<double> coordinates;

    Point(const std::vector<double>& coords) : coordinates(coords) {}
};

// Definición de un nodo en el árbol k-d
struct KDNode {
    Point point;
    KDNode* left;
    KDNode* right;

    KDNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
    // Constructor
    KDTree() : root(nullptr) {}

    // Función para insertar un punto en el árbol k-d
    void insert(const Point& point) {
        root = insertRecursive(root, point, 0);
    }

    // Función para buscar el punto más cercano en el árbol k-d
    Point findNearestNeighbor(const Point& target) const {
        double bestDistance = std::numeric_limits<double>::max();
        return findNearestNeighborRecursive(root, target, 0, bestDistance);
    }

private:
    // Función recursiva para insertar un punto en el árbol k-d
    KDNode* insertRecursive(KDNode* node, const Point& point, size_t depth) {
        if (!node) {
            return new KDNode(point);
        }

        size_t k = point.coordinates.size();
        size_t axis = depth % k;

        if (point.coordinates[axis] < node->point.coordinates[axis]) {
            node->left = insertRecursive(node->left, point, depth + 1);
        } else {
            node->right = insertRecursive(node->right, point, depth + 1);
        }

        return node;
    }

    // Función recursiva para buscar el punto más cercano en el árbol k-d
    Point findNearestNeighborRecursive(const KDNode* node, const Point& target, size_t depth, double& bestDistance) const {
        if (!node) {
            return Point({std::numeric_limits<double>::max(),std::numeric_limits<double>::max()}); // Punto vacío si el árbol está vacío
        }

        size_t k = target.coordinates.size();
        size_t axis = depth % k;

        const KDNode* nextBranch = (target.coordinates[axis] < node->point.coordinates[axis]) ? node->left : node->right;
        const KDNode* otherBranch = (nextBranch == node->left) ? node->right : node->left;

        Point best = findNearestNeighborRecursive(nextBranch, target, depth + 1, bestDistance);

        if (distanceSquared(target, best) > distanceSquared(target, node->point)) {
            best = node->point;
            bestDistance = distanceSquared(target, best);
        }

        if (std::abs(target.coordinates[axis] - node->point.coordinates[axis]) < std::sqrt(bestDistance)) {
            Point candidate = findNearestNeighborRecursive(otherBranch, target, depth + 1, bestDistance);
            if (distanceSquared(target, candidate) < bestDistance) {
                best = candidate;
            }
        }

        return best;
    }

    // Función auxiliar para calcular la distancia euclidiana cuadrada entre dos puntos
    double distanceSquared(const Point& p1, const Point& p2) const {
        double distance = 0.0;
        for (size_t i = 0; i < p1.coordinates.size(); ++i) {
            double diff = p1.coordinates[i] - p2.coordinates[i];
            distance += diff * diff;
        }
        
        distance = sqrt(distance);
        return distance;
    }

    KDNode* root;
};

int main() {
    // Ejemplo de uso
    KDTree kdTree;

    // Insertar puntos en el árbol
    kdTree.insert(Point({2, 3}));
    kdTree.insert(Point({5, 4}));
    kdTree.insert(Point({9, 6}));
    kdTree.insert(Point({4, 7}));
    kdTree.insert(Point({8, 1}));
    kdTree.insert(Point({7, 2}));

    // Buscar el punto más cercano al punto (6, 5)
    Point target({6, 5});
    Point nearestNeighbor = kdTree.findNearestNeighbor(target);

    // Imprimir el resultado
    std::cout << "Punto más cercano a (" << target.coordinates[0] << ", " << target.coordinates[1] << "): ("<< nearestNeighbor.coordinates[0] << ", " << nearestNeighbor.coordinates[1] << ")\n";

    return 0;
}
