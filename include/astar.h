#ifndef ADVENTURE_ASTAR_H
#define ADVENTURE_ASTAR_H

#include "utility"
#include "item.h"
using namespace std;

class AStar {
    class Node {
    public:
        int x;
        int y;
        int distance;

        Node(int x, int y, int distance) :
                x(x), y(y), distance(distance) {}
    };

    class Pre {
    public:
        int preX;
        int preY;
        int distance;

        Pre(int preX, int preY, int distance) :
                preX(preX), preY(preY), distance(distance) {}
    };

    class Cmp {
        static int predictedDistance(const Node &a);

    public:
        static Item *dest;

        bool operator()(const Node &a, const Node &b);
    };

public:

    pair<int, int> operator()(Item *fromItem, Item *toItem);
};

#endif //ADVENTURE_ASTAR_H
