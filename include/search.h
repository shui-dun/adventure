#ifndef ADVENTURE_SEARCH_H
#define ADVENTURE_SEARCH_H

#include "item.h"
#include <utility>
#include <functional>
using namespace std;

class Node {
public:
    int x;
    int y;
    int distance;
    Node *pre;

    Node(int x, int y, int distance, Node *pre) :
            x(x), y(y), distance(distance), pre(pre) {}
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

class AStar {
    class Cmp {
        static int predictedDistance(const Node *a);

    public:
        static Item *dest;

        bool operator()(const Node *a, const Node *b);
    };

public:

    pair<int, int> operator()(Item *fromItem, Item *toItem);
};

class BFS {
public:
    pair<Item *, pair<int, int>> operator()(Item *fromItem, const function<bool(Item *item)> &func);
};


#endif //ADVENTURE_SEARCH_H
