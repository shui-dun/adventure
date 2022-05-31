#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"

class MapUtils {
public:

    static void init();

    static void genWall();

    static void genRandomMap();

    static void draw();

    static void updateAxis(int x, int y, Item *item);
};


#endif //ADVENTURE_MAP_H
