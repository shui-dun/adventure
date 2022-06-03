#ifndef ADVENTURE_MIXIN_H
#define ADVENTURE_MIXIN_H

#include <random>
#include <vector>
#include <mutex>
#include "item.h"
#include "shooter.h"
using namespace std;

extern mt19937 randEngine;


extern vector<vector<Item *>> globalMap;

extern HeroShooter *myHero;

extern bool gameOver;

extern mutex mapMutex;

#endif //ADVENTURE_MIXIN_H
