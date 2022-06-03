#include "bullet.h"
#include "mixin.h"
#include "boxer.h"

Bullet::Bullet(int xPos, int yPos, int direction, int attackVal, Shooter &launcher, CampEnum camp)
        : Item(xPos, yPos, '*' | COLOR_PAIR(NORMAL_INIT), camp),
          Vulnerable(1, 0, 0),
          Aggressive(attackVal),
          Movable(4, 3),
          direction(direction),
          launcher(launcher) {}

bool Bullet::act() {
    auto p = MoveUtils::nextPosOfDirection(*this, direction);
    int newX = p.first, newY = p.second;
    if (globalMap[newX][newY] == nullptr) {
        MoveUtils::moveToPos(*this, newX, newY);
        return true;
    } else {
        if (dynamic_cast<Vulnerable *>(globalMap[newX][newY])) {
            attack(*dynamic_cast<Vulnerable *>(globalMap[newX][newY]));
        }
        AttackUtils::attack(1, *this);
        return false;
    }
}

bool Bullet::attack(Vulnerable &vulnerable) {
    int originHP = vulnerable.healthPoint;
    CampEnum oppositeCamp = dynamic_cast<Item &>(vulnerable).camp;
    bool isEnemy = (oppositeCamp != camp && oppositeCamp != OBJECT);
    bool alive = AttackUtils::attack(*this, vulnerable);
    int descHP = 0;
    if (alive) {
        descHP = vulnerable.healthPoint;
    }
    if (isEnemy) {
        launcher.score += originHP - descHP;
    }
    return alive;
}


