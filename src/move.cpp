#include "move.h"
#include <thread>
#include "mixin.h"
#include "hero.h"


pair<int, int> MoveUtils::moveWithDirection(Item &item, int direction) {
    int newX = item.xPos, newY = item.yPos;
    if (direction == 0) {
        newY -= 1;
    } else if (direction == 1) {
        newY += 1;
    } else if (direction == 2) {
        newX -= 1;
    } else {
        newX += 1;
    }
    return {newX, newY};
}

// 每个线程
void MoveUtils::p(Movable *character) {
    Item *itemCharacter = dynamic_cast<Item *>(character);
    int xPos = itemCharacter->xPos, yPos = itemCharacter->yPos;
    int timeInterval = character->timeInterval;
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(timeInterval));
        // 如果是由于自己的move导致的死亡，move返回false，再由自己所处的线程修改globalMap并delete自己
        // 如果是被别人杀死的，由杀死它的线程修改globalMap并delete
        if (globalMap[xPos][yPos] != itemCharacter) {
            return;
        }
        bool alive = character->move();
        xPos = itemCharacter->xPos, yPos = itemCharacter->yPos;
        if (!alive) {
            globalMap[xPos][yPos] = nullptr;
            delete character;
        }
    }
}