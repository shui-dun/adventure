#ifndef ADVENTURE_MOVE_H
#define ADVENTURE_MOVE_H

#include "item.h"
#include <utility>
using namespace std;

class Movable {
public:
    virtual ~Movable() = default;

    int timeInterval; // 两次移动间的时间间隔(ms)

    virtual bool move() = 0;
};

class MoveUtils {
public:
    static pair<int, int> moveWithDirection(Item &item, int direction);

    static void p(Movable *character);
};

#endif //ADVENTURE_MOVE_H
