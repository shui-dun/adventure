#include "attack.h"
#include "item.h"
#include "map.h"
#include "draw.h"

bool AttackUtils::attack(int attackVal, Vulnerable &attacked) {
    if (attacked.defendVal > attackVal) {
        return true;
    }
    attacked.healthPoint -= attackVal - attacked.defendVal;
    Item &attackedItem = dynamic_cast<Item &>(attacked);
    if (attacked.healthPoint <= 0) {
        if (dynamic_cast<HeroArcher *>(&attacked)) {
            MapUtils::gameOver = true;
        }
        MapUtils::gameMap[attackedItem.xPos][attackedItem.yPos] = nullptr;
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
        if (dynamic_cast<HeroArcher *>(&attacked)) {
            auto attack = dynamic_cast<Vulnerable *>(&attacker);
            if (attack) {
                DrawUtils::genCurEnemyInfo(*attack);
            }
        }
        return attack(attacker.attackVal, attacked);
    }
}

int AttackUtils::attackValGainOfEnemies() {
    return MapUtils::myHero->score / 30;
}

int AttackUtils::defendValGainOfEnemies() {
    return MapUtils::myHero->score / 50;
}

int AttackUtils::healthPointGainOfEnemies() {
    return MapUtils::myHero->score / 30;
}

