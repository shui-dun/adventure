#include "move.h"
#include <thread>
#include "mixin.h"
#include "hero.h"
#include "map.h"


pair<int, int> MoveUtils::nextPosOfDirection(Item &item, int direction) {
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

bool MoveUtils::shouldMove(Movable &movable) {
    movable.curTimeUnit = (movable.curTimeUnit + 1) % movable.timeUnits;
    return movable.curTimeUnit == 0;
}

void MoveUtils::moveAllCharacters() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
        mapMutex.lock();
        if (gameOver) {
            mapMutex.unlock();
            return;
        }
        for (int i = 1; i < MapUtils::cols - 1; ++i) {
            for (int j = 1; j < MapUtils::lines - 1; ++j) {
                auto movable = dynamic_cast<Movable *>(globalMap[i][j]);
                if (movable == nullptr)
                    continue;
                if (dynamic_cast<Hero *>(movable))
                    continue;
                if (!shouldMove(*movable))
                    continue;
                movable->act();
            }
        }
        refresh();
        mapMutex.unlock();
    }
}

void MoveUtils::moveMyHero() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(200));
        chtype inputChar = getch();
        mapMutex.lock();
        if (gameOver) {
            mapMutex.unlock();
            return;
        }
        myHero->inputChar = inputChar;
        myHero->act();
        refresh();
        mapMutex.unlock();
    }
}

void MoveUtils::moveToPos(Item &item, int newX, int newY) {
    MapUtils::updateAxis(item.xPos, item.yPos, nullptr);
    MapUtils::updateAxis(newX, newY, &item);
    item.xPos = newX;
    item.yPos = newY;
}
