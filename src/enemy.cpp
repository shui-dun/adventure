#include "enemy.h"
#include "mixin.h"
#include <random>
#include "hero.h"
#include "map.h"


RandomWalkEnemy::RandomWalkEnemy(int x, int y) {
    xPos = x;
    yPos = y;
    healthPoint = 6;
    symbol = '+' | COLOR_PAIR(NORMAL_INIT);
    attackVal = 2;
    timeInterval = 600;
}

bool RandomWalkEnemy::move() {
    uniform_int_distribution<int> distribution(0, 3);
    bool alive = true;
    while (true) {
        int direction = distribution(randEngine);
        auto p = MoveUtils::moveWithDirection(*this, direction);
        int newX = p.first, newY = p.second;
        if (globalMap[newX][newY] == nullptr) {
            MapUtils::updateAxis(xPos, yPos, nullptr);
            xPos = newX;
            yPos = newY;
            MapUtils::updateAxis(xPos, yPos, this);
            break;
        }
        if (dynamic_cast<Aggressive *>(globalMap[newX][newY])) {
            auto aggressive = dynamic_cast<Aggressive *>(globalMap[newX][newY]);
            int originHP = healthPoint;
            alive = beAttacked(*aggressive);
            if (dynamic_cast<Bullet *>(aggressive)) {
                myHero->score += originHP - healthPoint;
            }
        }
        if (dynamic_cast<Vulnerable *>(globalMap[newX][newY])) {
            auto attacked = dynamic_cast<Vulnerable *>(globalMap[newX][newY]);
            if (!attacked->beAttacked(*this)) {
                MapUtils::updateAxis(newX, newY, nullptr);
                delete attacked;
            }
            break;
        }
    }
    return alive;
}

bool RandomWalkEnemy::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, '+' | COLOR_PAIR(NORMAL_INJURED));
}

AStarEnemy::AStarEnemy(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = 'X' | COLOR_PAIR(NORMAL_INIT);
    healthPoint = 6;
    attackVal = 2;
    timeInterval = 800;
}

bool AStarEnemy::move() {
    int newX = xPos, newY = yPos;
    // A*搜索，尚待实现
    return true;
}

bool AStarEnemy::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, 'X' | COLOR_PAIR(NORMAL_INJURED));
}
