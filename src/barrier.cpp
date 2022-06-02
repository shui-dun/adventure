#include "barrier.h"
#include "bullet.h"
#include "mixin.h"

SolidBarrier::SolidBarrier(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = ' ' | COLOR_PAIR(SOLID_BARRIER);
}

WeakBarrier::WeakBarrier(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = ' ' | COLOR_PAIR(WEAK_BARRIER_INIT);
    healthPoint = 4;
    defendVal = 1;
}

bool WeakBarrier::beAttacked(Aggressive &attacker) {
    if (!dynamic_cast<Bullet *>(&attacker)) {
        return true;
    } else {
        return AttackUtils::attack(attacker, *this, ' ' | COLOR_PAIR(WEAK_BARRIER_INJURED));
    }
}