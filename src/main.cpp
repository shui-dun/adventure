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
    thread t1(MapUtils::createCharacters);
    thread t2(MapUtils::showInfo);
    thread t3(MoveUtils::moveMyHero);
    thread t4(MoveUtils::moveAllCharacters);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}