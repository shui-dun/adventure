#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"
#include "bullet.h"
#include "shooter.h"
#include <vector>
#include <random>
#include <mutex>

using namespace std;

class MapUtils {

    static bool shouldMove(Movable &movable);

public:
    static vector <vector<Item*>> gameMap;

    static HeroShooter *myHero;

    static bool gameOver;

    static mutex mapMutex;

    static mt19937 randEngine;

    static void init();

    static void genWall();

    static void genRandomMap();

    static void createInitCharacters();

    static bool isAxisLegal(int xPos, int yPos);

    static pair<int, int> nextPosOfDirection(Item &item, int direction);

    static void moveAllCharacters();

    static void moveMyHero();

    static void moveToPos(Item &item, int newX, int newY);

    static int nLines();

    static int nCols();

    static void createRandomCharacter();
};


#endif //ADVENTURE_MAP_H
