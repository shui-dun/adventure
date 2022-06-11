#include "arrow.h"
#include "draw.h"
#include "swordsman.h"

NormalArrow::NormalArrow(int xPos, int yPos, Archer &launcher)
        : Arrow(xPos, yPos, DrawUtils::ARROW_SYMBOL, launcher.color, launcher.camp,
                5, 3, 1, 0,
                launcher.arrowAttackVal, launcher.direction) {}

bool NormalArrow::act() {
    return ArrowUtils::defaultAction(*this);
}

bool NormalArrow::attack(Vulnerable &vulnerable) {
    return AttackUtils::attack(*this, vulnerable);
}

bool HeroArrow::act() {
    return ArrowUtils::defaultAction(*this);
}

HeroArrow::HeroArrow(int xPos, int yPos, HeroArcher &launcher)
        : Arrow(xPos, yPos, DrawUtils::ARROW_SYMBOL, launcher.color, launcher.camp,
                5, 3, 1, 0,
                launcher.arrowAttackVal, launcher.direction), launcher(launcher) {}

bool HeroArrow::attack(Vulnerable &vulnerable) {
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

bool ArrowUtils::defaultAction(Arrow &bullet) {
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
