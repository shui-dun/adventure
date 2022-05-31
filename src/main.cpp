#include <iostream>
#include <cursesw.h>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include "item.h"
#include "map.h"
#include "movable.h"
#include "mixin.h"
using namespace std;

// 每个线程
void p(Movable &character) {
    Item &itemCharacter = dynamic_cast<Item &>(character);
    int xPos = itemCharacter.xPos, yPos = itemCharacter.yPos;
    int timeInterval = character.timeInterval;
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(timeInterval));
        // 如果是由于自己的move导致的死亡，move返回false，再由自己所处的线程修改globalMap并delete自己
        // 如果是被别人杀死的，由杀死它的线程修改globalMap并delete
        if (globalMap[xPos][yPos] != &itemCharacter) {
            return;
        }
        bool alive = character.move();
        xPos = itemCharacter.xPos, yPos = itemCharacter.yPos;
        if (!alive) {
            globalMap[xPos][yPos] = nullptr;
            delete &character;
        }

    }
}

int main() {
    std::random_device rd;
    randEngine.seed(rd());
    MapUtils::init();
    getch();
    return 0;
}