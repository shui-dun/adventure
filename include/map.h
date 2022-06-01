#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"
#include "bullet.h"

class MapUtils {
public:

    static void init();

    static void genWall();

    static void genRandomMap();

    static void draw();

    static void updateAxis(int x, int y, Item *item);

    static void createCharacters();

    static void showInfo();
};


#endif //ADVENTURE_MAP_H
