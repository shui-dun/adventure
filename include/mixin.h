#ifndef ADVENTURE_MIXIN_H
#define ADVENTURE_MIXIN_H

#include <random>
#include <vector>
#include "item.h"
using namespace std;

extern mt19937 randEngine;

enum colors {
    BACKGROUND = 1,
    FRONT,
    SOLID_BARRIER,
    WEAK_BARRIER_INIT,
    WEAK_BARRIER_INJURED,
    NORMAL_INIT,
    NORMAL_INJURED,
    ME,
    CURE_POTION,
    STRENGTHEN_POTION
};

extern vector<vector<Item *>> globalMap;

#endif //ADVENTURE_MIXIN_H
