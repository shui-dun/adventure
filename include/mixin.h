#ifndef ADVENTURE_MIXIN_H
#define ADVENTURE_MIXIN_H

#include <random>
#include <vector>
#include <mutex>
#include "item.h"
#include "shooter.h"
using namespace std;

extern mt19937 randEngine;

enum colorEnum {
    BACKGROUND = 1,
    INFO,
    INFO2,
    SOLID_BARRIER,
    WEAK_BARRIER_INIT,
    WEAK_BARRIER_INJURED,
    NORMAL_INIT,
    NORMAL_INJURED,
    ME,
    POTION
};

extern vector<vector<Item *>> globalMap;

extern Shooter *myHero;

extern bool gameOver;

extern mutex mapMutex;

#endif //ADVENTURE_MIXIN_H
