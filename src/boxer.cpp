#include "boxer.h"
#include "mixin.h"
#include <random>
#include "shooter.h"
#include "map.h"
#include "barrier.h"


RandomWalkBoxer::RandomWalkBoxer(int xPos, int yPos)
        : Boxer(xPos, yPos, '+', COLOR_PAIR(MapUtils::NORMAL),
                6 + AttackUtils::healthPointGainOfEnemies(),
                1 + AttackUtils::defendValGainOfEnemies(),
                3 + AttackUtils::attackValGainOfEnemies(),
                8, randEngine() % 6, ENEMY) {}

bool RandomWalkBoxer::act() {
    uniform_int_distribution<int> distribution(0, 3);
    int direction = distribution(randEngine);
    auto p = MoveUtils::nextPosOfDirection(*this, direction);
    int newX = p.first, newY = p.second;
    if (globalMap[newX][newY] == nullptr) {
        MoveUtils::moveToPos(*this, newX, newY);
        return true;
    } else if (dynamic_cast<Vulnerable *>(globalMap[newX][newY])) {
        auto &attacked = dynamic_cast<Vulnerable &>(*globalMap[newX][newY]);
        bool aliveOfEnemy = attack(attacked);
        if (aliveOfEnemy) {
            if (dynamic_cast<Aggressive *>(globalMap[newX][newY])) {
                auto &aggressive = dynamic_cast<Aggressive &>(*globalMap[newX][newY]);
                return aggressive.attack(*this);
            } else {
                return true;
            }
        } else {
            MoveUtils::moveToPos(*this, newX, newY);
            return true;
        }
    } else if (dynamic_cast<Aggressive *>(globalMap[newX][newY])) {
        auto &aggressive = dynamic_cast<Aggressive &>(*globalMap[newX][newY]);
        return aggressive.attack(*this);
    } else {
        return true;
    }
}

bool RandomWalkBoxer::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}


SmartBoxer::SmartBoxer(int xPos, int yPos)
        : Boxer(xPos, yPos, '+', COLOR_PAIR(MapUtils::NORMAL),
                6 + AttackUtils::healthPointGainOfEnemies(),
                1 + AttackUtils::defendValGainOfEnemies(),
                3 + AttackUtils::attackValGainOfEnemies(),
                8, randEngine() % timeUnits,
                ENEMY) {}

bool SmartBoxer::act() {
    // A*搜索，尚待实现
    return true;
}

bool SmartBoxer::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}

