#ifndef ADVENTURE_MIXIN_H
#define ADVENTURE_MIXIN_H

#include <random>
#include <vector>
#include <mutex>
#include "item.h"
#include "hero.h"
using namespace std;

extern mt19937 randEngine;

enum colors {
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

extern Hero *myHero;

extern mutex mapMutex;

#endif //ADVENTURE_MIXIN_H
