#include "bullet.h"
#include "mixin.h"
#include "enemy.h"

Bullet::Bullet(int x, int y, int direction, int attackVal) {
    xPos = x;
    yPos = y;
    symbol = '*' | COLOR_PAIR(NORMAL_INIT);
    healthPoint = 1;
    this->attackVal = attackVal;
    timeUnits = 4;
    curTimeUnit = timeUnits - 1;
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
        attack(globalMap[newX][newY]);
        return false;
    }
}

bool Bullet::beAttacked(Aggressive &attacker) {
    return false;
}

bool Bullet::shouldIMove() {
    return MoveUtils::defaultShouldIMove(*this);
}

void Bullet::attack(Item *item) {
    if (dynamic_cast<Vulnerable *>(item)) {
        auto impacted = dynamic_cast<Vulnerable *>(item);
        int originHP = impacted->healthPoint;
        bool alive = impacted->beAttacked(*this);
        int descHP = impacted->healthPoint;
        if (dynamic_cast<Enemy *>(impacted)) {
            myHero->score += originHP - descHP;
        }
        if (!alive) {
            MapUtils::updateAxis(item->xPos, item->yPos, nullptr);
            delete item;
        }
    }
}
