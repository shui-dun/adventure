#include "hero.h"
#include "mixin.h"


Hero::Hero(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = 'O' | COLOR_PAIR(ME);
    attackVal = 2;
    healthPoint = 20;
    timeInterval = 100;
}

bool Hero::move() {
    // 按照用户输入
    return true;
}

bool Hero::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, this->symbol);
}
