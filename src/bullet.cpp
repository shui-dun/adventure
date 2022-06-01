#include "bullet.h"
#include "mixin.h"
#include "enemy.h"

Bullet::Bullet(int x, int y, int direction) {
    xPos = x;
    yPos = y;
    symbol = '*' | COLOR_PAIR(NORMAL_INIT);
    healthPoint = 1;
    attackVal = 2;
    timeInterval = 400;
    this->direction = direction;

}

bool Bullet::move() {
    auto p = MoveUtils::moveWithDirection(*this, direction);
    int newX = p.first, newY = p.second;

    if (globalMap[newX][newY] == nullptr) {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        MapUtils::updateAxis(newX, newY, this);
        xPos = newX;
        yPos = newY;
        return true;
    } else {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        Item *item = globalMap[newX][newY];
        if (dynamic_cast<Vulnerable *>(item)) {
            auto impacted = dynamic_cast<Vulnerable *>(item);
            int originHP = impacted->healthPoint;
            bool alive = impacted->beAttacked(*this);
            int descHP = impacted->healthPoint;
            if (dynamic_cast<Enemy *>(impacted)) {
                myHero->score += originHP - descHP;
            }
            if (!alive) {
                delete item;
                MapUtils::updateAxis(newX, newY, nullptr);
            }
        }
        return false;
    }
}

bool Bullet::beAttacked(Aggressive &attacker) {
    return false;
}
