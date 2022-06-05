#include "boxer.h"
#include "draw.h"
#include <random>
#include "shooter.h"
#include "map.h"
#include "barrier.h"


RandomWalkBoxer::RandomWalkBoxer(int xPos, int yPos)
        : Boxer(xPos, yPos, DrawUtils::BOXER_SYMBOL, COLOR_PAIR(DrawUtils::ENEMY),
                6 + AttackUtils::healthPointGainOfEnemies(),
                1 + AttackUtils::defendValGainOfEnemies(),
                3 + AttackUtils::attackValGainOfEnemies(),
                8, MapUtils::randEngine() % 6, ENEMY) {}

bool RandomWalkBoxer::act() {
    uniform_int_distribution<int> distribution(0, 3);
    int direction = distribution(MapUtils::randEngine);
    auto p = MapUtils::nextPosOfDirection(*this, direction);
    int newX = p.first, newY = p.second;
    if (MapUtils::gameMap[newX][newY] == nullptr) {
        MapUtils::moveToPos(*this, newX, newY);
        return true;
    } else if (dynamic_cast<Vulnerable *>(MapUtils::gameMap[newX][newY])) {
        auto &attacked = dynamic_cast<Vulnerable &>(*MapUtils::gameMap[newX][newY]);
        bool aliveOfEnemy = attack(attacked);
        if (aliveOfEnemy) {
            if (dynamic_cast<Aggressive *>(MapUtils::gameMap[newX][newY])) {
                auto &aggressive = dynamic_cast<Aggressive &>(*MapUtils::gameMap[newX][newY]);
                return aggressive.attack(*this);
            } else {
                return true;
            }
        } else {
            MapUtils::moveToPos(*this, newX, newY);
            return true;
        }
    } else if (dynamic_cast<Aggressive *>(MapUtils::gameMap[newX][newY])) {
        auto &aggressive = dynamic_cast<Aggressive &>(*MapUtils::gameMap[newX][newY]);
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
        : Boxer(xPos, yPos, DrawUtils::BOXER_SYMBOL, COLOR_PAIR(DrawUtils::ENEMY),
                6 + AttackUtils::healthPointGainOfEnemies(),
                1 + AttackUtils::defendValGainOfEnemies(),
                3 + AttackUtils::attackValGainOfEnemies(),
                8, MapUtils::randEngine() % timeUnits,
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

