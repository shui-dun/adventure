#include "enemy.h"
#include "mixin.h"
#include <random>
#include "hero.h"
#include "map.h"


RandomWalkEnemy::RandomWalkEnemy(int xPos, int yPos)
        : Enemy(xPos, yPos, '+' | COLOR_PAIR(NORMAL_INIT), 6, 1,
                3, 6, randEngine() % 6) {}

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
                dynamic_cast<Bullet *>(aggressive)->launcher.score += originHP - healthPoint;
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
    if (!alive)
        MapUtils::updateAxis(xPos, yPos, nullptr);
    return alive;
}

bool RandomWalkEnemy::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, '+' | COLOR_PAIR(NORMAL_INJURED));
}

bool RandomWalkEnemy::shouldIMove() {
    return MoveUtils::defaultShouldIMove(*this);
}

AStarEnemy::AStarEnemy(int xPos, int yPos)
        : Enemy(xPos, yPos, 'X' | COLOR_PAIR(NORMAL_INIT), 6, 1,
                3, 7, randEngine() % timeUnits) {}

bool AStarEnemy::move() {
    int newX = xPos, newY = yPos;
    // A*搜索，尚待实现
    return true;
}

bool AStarEnemy::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, 'X' | COLOR_PAIR(NORMAL_INJURED));
}

bool AStarEnemy::shouldIMove() {
    return MoveUtils::defaultShouldIMove(*this);
}
