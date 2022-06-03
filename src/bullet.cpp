#include "bullet.h"
#include "mixin.h"
#include "boxer.h"

NormalBullet::NormalBullet(int xPos, int yPos, int direction, int attackVal, Item::CampEnum camp)
        : Bullet(xPos, yPos, '*' | COLOR_PAIR(NORMAL_INIT), camp,
                 4, 3, 1, 0, 0,
                 attackVal, direction) {}

bool NormalBullet::act() {
    return BulletUtils::defaultAction(*this);
}

bool NormalBullet::attack(Vulnerable &vulnerable) {
    return AttackUtils::attack(*this, vulnerable);
}

bool HeroBullet::act() {
    return BulletUtils::defaultAction(*this);
}

HeroBullet::HeroBullet(int xPos, int yPos, int direction,
                       int attackVal, Item::CampEnum camp,
                       HeroShooter &launcher)
        : Bullet(xPos, yPos, '*' | COLOR_PAIR(NORMAL_INIT), camp,
                 4, 3, 1, 0, 0,
                 attackVal, direction), launcher(launcher) {}

bool HeroBullet::attack(Vulnerable &vulnerable) {
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

bool BulletUtils::defaultAction(Bullet &bullet) {
    auto p = MoveUtils::nextPosOfDirection(bullet, bullet.direction);
    int newX = p.first, newY = p.second;
    if (globalMap[newX][newY] == nullptr) {
        MoveUtils::moveToPos(bullet, newX, newY);
        return true;
    } else {
        auto vulnerable = dynamic_cast<Vulnerable *>(globalMap[newX][newY]);
        if (vulnerable) {
            bullet.attack(*vulnerable);
        }
        AttackUtils::attack(1, bullet);
        return false;
    }
}
