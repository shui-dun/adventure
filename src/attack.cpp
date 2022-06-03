#include "attack.h"
#include "item.h"
#include "map.h"
#include "mixin.h"

bool AttackUtils::attack(int attackVal, Vulnerable &attacked) {
    if (attacked.defendVal > attackVal) {
        return true;
    }
    attacked.healthPoint -= attackVal - attacked.defendVal;
    Item &attackedItem = dynamic_cast<Item &>(attacked);
    if (attacked.healthPoint <= 0) {
        if (dynamic_cast<HeroShooter *>(&attacked)) {
            gameOver = true;
        }
        MapUtils::updateAxis(attackedItem.xPos, attackedItem.yPos, nullptr);
        delete &attacked;
        return false;
    } else {
        return true;
    }
}

bool AttackUtils::attack(Aggressive &attacker, Vulnerable &attacked) {
    if (dynamic_cast<Item &>(attacker).camp == dynamic_cast<Item &>(attacked).camp) {
        return true;
    } else {
        return attack(attacker.attackVal, attacked);
    }
}

int AttackUtils::attackValGainOfEnemies() {
    return myHero->score / 30;
}

int AttackUtils::defendValGainOfEnemies() {
    return myHero->score / 50;
}

int AttackUtils::healthPointGainOfEnemies() {
    return myHero->score / 30;
}

