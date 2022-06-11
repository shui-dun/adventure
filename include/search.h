#ifndef ADVENTURE_SEARCH_H
#define ADVENTURE_SEARCH_H

#include "item.h"
#include <utility>
#include <functional>
using namespace std;

/**
 * 使用各搜索算法进行搜索时，都会保存这样的路径链表
 * 每个节点保存节点的坐标、离出发点的距离、上一个节点等信息
 */
class Node {
public:
    /** x坐标 */
    int x;

    /** y坐标 */
    int y;

    /** 离出发点的距离 */
    int distance;

    /** 指向上一个节点的指针 */
    Node *pre;

    Node(int x, int y, int distance, Node *pre) :
            x(x), y(y), distance(distance), pre(pre) {}
};

/**
 * 计算坐标的hash值
 * 其中，坐标是形如(x,y)的整数对
 */
class AxisHash {
    template<class T>
    inline void hash_combine(std::size_t &seed, const T &v) const {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

public:
    size_t operator()(const pair<int, int> &node) const;
};

/**
 * A*算法
 */
class AStar {
    class Cmp {
        static int predictedDistance(const Node *a);

    public:
        static Item *dest;

        /**
         * 使用代价函数比较两个节点的大小
         * 代价函数f(n)=g(n)+h(n)
         * 其中g(n)是节点n距离起点的代价，
         * h(n)是节点n距离终点的预计代价，这里使用了曼哈顿距离
         */
        bool operator()(const Node *a, const Node *b);
    };

public:

    /**
     * 使用A*算法进行搜索
     * @param fromItem 起点
     * @param toItem 终点
     * @return 下一步行动的坐标，(-1,-1)代表找不到从起点到终点的路径
     */
    pair<int, int> operator()(Item *fromItem, Item *toItem);
};

/**
 * 广度优先搜索
 */
class BFS {
public:
    /**
     * 使用BFS算法搜索通向某物品的路径，该物品是离起点最近的满足指定条件的物品
     * @param fromItem 起点
     * @param func 判断函数，我们是要搜索满足该函数的物品
     * @return 返回搜索到的节点，与为了到达该节点下一步应到达的坐标(x,y)
     */
    pair<Item *, pair<int, int>> operator()(Item *fromItem, const function<bool(Item *item)> &func);
};


#endif //ADVENTURE_SEARCH_H
