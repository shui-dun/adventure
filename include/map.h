#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"
#include "bullet.h"

class MapUtils {
    static void createRandomCharacter();

public:

    enum colorEnum {
        BACKGROUND = 1,
        INFO,
        INFO2,
        SOLID_BARRIER,
        WEAK_BARRIER,
        NORMAL,
        MIND_CONTROL,
        ME,
        POTION
    };

    static int lines;

    static int cols;

    static void init();

    static void initColor();

    static void genWall();

    static void genRandomMap();

    static void drawInit();

    static void updateAxis(int x, int y, Item *item);

    static void createCharacters();

    static void showInfo();

    static void pause();

    static void showGameOver();

    static bool isAxisLegal(int xPos, int yPos);
};


#endif //ADVENTURE_MAP_H
