#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <set>
#include "movable.hpp"
using namespace std;

class Map {
public:
    vector<vector<Item *>> items;



    Map() {

    }

    void genRandomMap() {
        // 除了这种点状地图，以后还要产生几种迷宫地图
    }

    void draw() {

    }
};

Map globalMap;

// 还要加上每个单元的锁以及整个地图的锁
// 还要加上判断每个单元死没死的布尔值，不然线程不知道它操作的角色死了

#endif