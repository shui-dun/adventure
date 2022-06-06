#include "boxer.h"
#include "draw.h"
#include <random>
#include "shooter.h"
#include "map.h"
#include "barrier.h"
#include "astar.h"


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
    return BoxerUtils::defaultAction(this, p.first, p.second);
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
                8, MapUtils::randEngine() % 8,
                ENEMY) {}

bool SmartBoxer::act() {
    auto p = AStar()(this, MapUtils::myHero);
    if (p.first == -1) {
        return true;
    }
    return BoxerUtils::defaultAction(this, p.first, p.second);
}

bool SmartBoxer::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}

bool BoxerUtils::defaultAction(Boxer *boxer, int newX, int newY) {
    if (!MapUtils::gameMap[newX][newY]) {
        MapUtils::moveToPos(*boxer, newX, newY);
        return true;
    } else if (dynamic_cast<Vulnerable *>(MapUtils::gameMap[newX][newY])) {
        auto &attacked = dynamic_cast<Vulnerable &>(*MapUtils::gameMap[newX][newY]);
        bool aliveOfEnemy = boxer->attack(attacked);
        if (aliveOfEnemy) {
            if (dynamic_cast<Aggressive *>(MapUtils::gameMap[newX][newY])) {
                auto &aggressive = dynamic_cast<Aggressive &>(*MapUtils::gameMap[newX][newY]);
                return aggressive.attack(*boxer);
            } else {
                return true;
            }
        } else {
            MapUtils::moveToPos(*boxer, newX, newY);
            return true;
        }
    } else if (dynamic_cast<Aggressive *>(MapUtils::gameMap[newX][newY])) {
        auto &aggressive = dynamic_cast<Aggressive &>(*MapUtils::gameMap[newX][newY]);
        return aggressive.attack(*boxer);
    } else {
        return true;
    }
}
