#ifndef ADVENTURE_MOVE_H
#define ADVENTURE_MOVE_H

#include "item.h"
#include <utility>
using namespace std;

class Movable {
public:
    virtual ~Movable() = default;

    unsigned int timeUnits; // 两次移动间的时间间隔

    unsigned int curTimeUnit;

    virtual bool move() = 0;

    virtual bool shouldIMove() = 0;
};

class MoveUtils {
public:
    static pair<int, int> moveWithDirection(Item &item, int direction);

    static bool defaultShouldIMove(Movable &movable);

    static void moveAllCharacters();

    static void moveMyHero();
};

#endif //ADVENTURE_MOVE_H
