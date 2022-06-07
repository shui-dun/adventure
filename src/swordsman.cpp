#include "swordsman.h"
#include "draw.h"
#include <random>
#include "archer.h"
#include "map.h"
#include "barrier.h"
#include "search.h"


RandomWalkSwordsman::RandomWalkSwordsman(int xPos, int yPos)
        : Swordsman(xPos, yPos, DrawUtils::BOXER_SYMBOL, COLOR_PAIR(DrawUtils::RANDOM_WALK_ENEMY),
                    6 + AttackUtils::healthPointGainOfEnemies(),
                    1 + AttackUtils::defendValGainOfEnemies(),
                    3 + AttackUtils::attackValGainOfEnemies(),
                    8, MapUtils::randEngine() % 6, ENEMY) {}

bool RandomWalkSwordsman::act() {
    uniform_int_distribution<int> distribution(0, 3);
    int direction = distribution(MapUtils::randEngine);
    auto p = MapUtils::nextPosOfDirection(*this, direction);
    return SwordsmanUtils::defaultAction(this, p.first, p.second);
}

bool RandomWalkSwordsman::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}


SmartSwordsman::SmartSwordsman(int xPos, int yPos)
        : Swordsman(xPos, yPos, DrawUtils::BOXER_SYMBOL, COLOR_PAIR(DrawUtils::SMART_ENEMY),
                    6 + AttackUtils::healthPointGainOfEnemies(),
                    1 + AttackUtils::defendValGainOfEnemies(),
                    3 + AttackUtils::attackValGainOfEnemies(),
                    8, MapUtils::randEngine() % 8,
                    ENEMY) {}

bool SmartSwordsman::act() {
    pair<int, int> p;
    if (camp == ENEMY) {
        p = AStar()(this, MapUtils::myHero);
    } else {
        p = BFS()(this, [](Item *item) -> bool {
            return item->camp == ENEMY && !dynamic_cast<Arrow *>(item);
        }).second;
    }
    if (p.first == -1) {
        return true;
    }
    return SwordsmanUtils::defaultAction(this, p.first, p.second);
}

bool SmartSwordsman::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}

bool SwordsmanUtils::defaultAction(Swordsman *boxer, int newX, int newY) {
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
