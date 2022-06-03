#include "enemy.h"
#include "mixin.h"
#include <random>
#include "hero.h"
#include "map.h"
#include "barrier.h"


RandomWalkEnemy::RandomWalkEnemy(int xPos, int yPos)
        : Enemy(xPos, yPos, '+' | COLOR_PAIR(NORMAL_INIT), 6, 1,
                3, 60, randEngine() % 6,
                '+' | COLOR_PAIR(NORMAL_INJURED)) {}

bool RandomWalkEnemy::act() {
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

bool RandomWalkEnemy::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(attackVal, vulnerable);
    }
}


AStarEnemy::AStarEnemy(int xPos, int yPos)
        : Enemy(xPos, yPos, 'X' | COLOR_PAIR(NORMAL_INIT), 6, 1,
                3, 7, randEngine() % timeUnits,
                'X' | COLOR_PAIR(NORMAL_INJURED)) {}

bool AStarEnemy::act() {
    // A*搜索，尚待实现
    return true;
}

bool AStarEnemy::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) {
        return true;
    } else {
        return AttackUtils::attack(attackVal, vulnerable);
    }
}

