#include "bullet.h"
#include "draw.h"
#include "boxer.h"

NormalBullet::NormalBullet(int xPos, int yPos, Shooter &launcher)
        : Bullet(xPos, yPos, DrawUtils::BULLET_SYMBOL, launcher.color, launcher.camp,
                 5, 3, 1, 0,
                 launcher.bulletAttackVal, launcher.direction) {}

bool NormalBullet::act() {
    return BulletUtils::defaultAction(*this);
}

bool NormalBullet::attack(Vulnerable &vulnerable) {
    return AttackUtils::attack(*this, vulnerable);
}

bool HeroBullet::act() {
    return BulletUtils::defaultAction(*this);
}

HeroBullet::HeroBullet(int xPos, int yPos, HeroShooter &launcher)
        : Bullet(xPos, yPos, DrawUtils::BULLET_SYMBOL, launcher.color, launcher.camp,
                 5, 3, 1, 0,
                 launcher.bulletAttackVal, launcher.direction), launcher(launcher) {}

bool HeroBullet::attack(Vulnerable &vulnerable) {
    int originHP = vulnerable.healthPoint;
    CampEnum oppositeCamp = dynamic_cast<Item &>(vulnerable).camp;
    if (oppositeCamp != camp) {
        DrawUtils::genCurEnemyInfo(vulnerable);
    }
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
    auto p = MapUtils::nextPosOfDirection(bullet, bullet.direction);
    int newX = p.first, newY = p.second;
    if (!MapUtils::gameMap[newX][newY]) {
        MapUtils::moveToPos(bullet, newX, newY);
        return true;
    } else {
        auto vulnerable = dynamic_cast<Vulnerable *>(MapUtils::gameMap[newX][newY]);
        if (vulnerable) {
            bullet.attack(*vulnerable);
        }
        AttackUtils::attack(1, bullet);
        return false;
    }
}
