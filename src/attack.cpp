#include "attack.h"
#include "item.h"
#include "map.h"
#include "draw.h"

bool AttackUtils::attack(int attackVal, Vulnerable &attacked) {
    if (attacked.defendVal > attackVal) { // 被攻击者的防御值大于攻击者的攻击值，则被攻击者不受伤害
        return true;
    }
    attacked.healthPoint -= attackVal - attacked.defendVal; // 被攻击者受到伤害
    Item &attackedItem = dynamic_cast<Item &>(attacked);
    if (attacked.healthPoint <= 0) { // 如果被攻击者的血量小于等于0，则死亡
        if (dynamic_cast<HeroArcher *>(&attacked)) {
            MapUtils::gameOver = true;
            MapUtils::myHero = nullptr;
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
        // 如果攻击者和被攻击者属于同一阵营，则不进行攻击行为
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

