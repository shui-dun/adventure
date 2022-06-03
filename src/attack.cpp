#include "attack.h"
#include "item.h"
#include "map.h"

bool AttackUtils::attack(Aggressive &attacker, Vulnerable &attacked) {
    if (attacked.defendVal > attacker.attackVal) {
        return true;
    }
    attacked.healthPoint -= attacker.attackVal - attacked.defendVal;
    Item &attackedItem = dynamic_cast<Item &>(attacked);
    if (attacked.healthPoint <= attacked.initHealthPoint / 2 && attacked.injuredSymbol != 0) {
        attackedItem.symbol = attacked.injuredSymbol;
        MapUtils::updateAxis(attackedItem.xPos, attackedItem.yPos, &attackedItem);
    }
    if (attacked.healthPoint <= 0) {
        return false;
    } else {
        return true;
    }
}