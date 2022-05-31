#include "bullet.h"
#include "mixin.h"
#include "map.h"

Bullet::Bullet(int x, int y, int direction) {
    xPos = x;
    yPos = y;
    symbol = '*' | COLOR_PAIR(NORMAL_INIT);
    healthPoint = 1;
    attackVal = 2;
    timeInterval = 200;
    this->direction = direction;

}

bool Bullet::move() {
    int newX = xPos, newY = yPos;
    if (direction == 0) {
        newY -= 1;
    } else if (direction == 1) {
        newY += 1;
    } else if (direction == 2) {
        newX -= 1;
    } else {
        newX += 1;
    }
    if (globalMap[newX][newY] == nullptr) {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        MapUtils::updateAxis(newX, newY, this);
        return true;
    } else {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        Item *impacted = globalMap[newX][newY];
        if (dynamic_cast<Vulnerable *>(impacted)) {
            auto impacted1 = dynamic_cast<Vulnerable *>(impacted);
            if (!impacted1->beAttacked(*this)) {
                delete impacted;
                MapUtils::updateAxis(newX, newY, nullptr);
            }
        }
        return false;
    }
}

bool Bullet::beAttacked(Aggressive &attacker) {
    return false;
}
