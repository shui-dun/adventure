#include <iostream>
#include <cursesw.h>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include "item.h"
#include "map.h"
#include "potion.h"
#include "move.h"
#include "mixin.h"
#include "hero.h"
using namespace std;

int main() {
    std::random_device rd;
    randEngine.seed(rd());
    MapUtils::init();
    MapUtils::createCharacters();
    return 0;
}