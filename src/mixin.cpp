#include "mixin.h"

mt19937 randEngine;

vector<vector<Item *>> globalMap;

Shooter *myHero;

bool gameOver;

mutex mapMutex;