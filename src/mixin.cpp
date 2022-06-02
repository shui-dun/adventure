#include "mixin.h"

mt19937 randEngine;

vector<vector<Item *>> globalMap;

Hero *myHero;

bool gameOver;

mutex mapMutex;