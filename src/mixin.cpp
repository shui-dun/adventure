#include "mixin.h"

mt19937 randEngine;

vector<vector<Item *>> globalMap;

HeroShooter *myHero;

bool gameOver;

mutex mapMutex;