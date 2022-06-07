#ifndef ADVENTURE_ASTAR_H
#define ADVENTURE_ASTAR_H

#include "item.h"
#include <utility>
#include <functional>
using namespace std;

class AStar {
    class Node {
    public:
        int x;
        int y;
        int distance;
        Node *pre;

        Node(int x, int y, int distance, Node *pre) :
                x(x), y(y), distance(distance), pre(pre) {}
    };

    class Cmp {
        static int predictedDistance(const Node *a);

    public:
        static Item *dest;

        bool operator()(const Node *a, const Node *b);
    };

    class AxisHash {
        template<class T>
        inline void hash_combine(std::size_t &seed, const T &v) const {
            std::hash<T> hasher;
            seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

    public:
        size_t operator()(const pair<int, int> &node) const;
    };

public:

    pair<int, int> operator()(Item *fromItem, Item *toItem);
};


#endif //ADVENTURE_ASTAR_H
