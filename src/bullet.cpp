#include "bullet.h"
#include "mixin.h"
#include "enemy.h"

Bullet::Bullet(int xPos, int yPos, int direction, int attackVal, Hero &launcher)
        : Item(xPos, yPos, '*' | COLOR_PAIR(NORMAL_INIT)),
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
    bool isEnemy = dynamic_cast<Enemy *>(&vulnerable) != nullptr;
    bool alive = AttackUtils::attack(attackVal, vulnerable);
    int descHP = 0;
    if (alive) {
        descHP = vulnerable.healthPoint;
    }
    if (isEnemy) {
        launcher.score += originHP - descHP;
    }
    return alive;
}


