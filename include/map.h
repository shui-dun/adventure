#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"
#include "bullet.h"
#include "shooter.h"
#include <vector>
#include <utility>
#include <random>
#include <mutex>

using namespace std;

class MapUtils {

    static bool shouldMove(Movable &movable);

    static void genLineOfWall(int fromY, int toY, int x, bool horizontal);

public:
    static vector<vector<Item *>> gameMap;

    static HeroShooter *myHero;

    static bool gameOver;

    static mutex mapMutex;

    static mt19937 randEngine;

    static void init();

    static void genWall();

    static void genRandomMap();

    static void genRecursiveSegmentationMap(int xFrom, int yFrom, int xTo, int yTo);

    static void createInitCharacters();

    static bool isAxisLegal(int xPos, int yPos);

    static pair<int, int> nextPosOfDirection(Item &item, int direction);

    static pair<int, int> nextPosOfDirection(int x, int y, int direction);

    static void moveAllCharacters();

    static void moveMyHero();

    static void moveToPos(Item &item, int newX, int newY);

    static int nLines();

    static int nCols();

    static void createRandomCharacter();

    static int locatedAtDirection(Item &me, int destX, int destY);
};


#endif //ADVENTURE_MAP_H
