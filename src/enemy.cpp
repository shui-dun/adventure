#include "enemy.h"
#include "mixin.h"


RandomWalkEnemy::RandomWalkEnemy(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = '+' | COLOR_PAIR(NORMAL_INIT);
    healthPoint = 6;
    attackVal = 2;
    timeInterval = 200;
}

bool RandomWalkEnemy::move() {
    int newX = xPos, newY = yPos;

    return true;
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
    timeInterval = 200;
}

bool AStarEnemy::move() {
    int newX = xPos, newY = yPos;
    // A*搜索，尚待实现
    return true;
}

bool AStarEnemy::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, 'X' | COLOR_PAIR(NORMAL_INJURED));
}
