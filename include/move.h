#ifndef ADVENTURE_MOVE_H
#define ADVENTURE_MOVE_H

#include "item.h"
#include <utility>
using namespace std;

class Movable {
public:
    Movable(unsigned int timeUnits, unsigned int curTimeUnit) : timeUnits(timeUnits), curTimeUnit(curTimeUnit) {}

    virtual ~Movable() = default;

    unsigned int timeUnits; // 两次移动间的时间间隔

    unsigned int curTimeUnit;

    virtual bool act() = 0;
};

class MoveUtils {
public:
    static pair<int, int> nextPosOfDirection(Item &item, int direction);

    static void moveToPos(Item &item, int newX, int newY);

    static bool shouldMove(Movable &movable);

    static void moveAllCharacters();

    static void moveMyHero();
};

#endif //ADVENTURE_MOVE_H
