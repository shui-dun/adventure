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
#include "shooter.h"
using namespace std;

int main() {
    std::random_device rd;
    randEngine.seed(rd());
    MapUtils::init();
    thread t1(MapUtils::createCharacters);
    thread t2(MoveUtils::moveMyHero);
    thread t3(MoveUtils::moveAllCharacters);
    thread t4(MapUtils::showInfo);
    t1.detach();
    t2.detach();
    t3.detach();
    t4.join();
    MapUtils::showGameOver();
    return 0;
}