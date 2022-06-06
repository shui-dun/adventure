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
#include "draw.h"
#include "archer.h"
using namespace std;

void runGame() {
    uniform_real_distribution<float> distribution(0.0, 1.0);
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
        MapUtils::mapMutex.lock();

        if (MapUtils::gameOver) {
            MapUtils::mapMutex.unlock();
            return;
        }

        MapUtils::moveAllCharacters();

        if (distribution(MapUtils::randEngine) < 0.016) {
            MapUtils::createRandomCharacter();
        }

        DrawUtils::draw();

        MapUtils::mapMutex.unlock();
    }
}

int main() {
    MapUtils::randEngine.seed(random_device()());
    DrawUtils::init();
    MapUtils::init();
    thread t(MapUtils::moveMyHero);
    runGame();
    t.detach();
    DrawUtils::showGameOver();
    return 0;
}