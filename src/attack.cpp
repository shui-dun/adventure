#include "attack.h"
#include "item.h"
#include "map.h"

bool AttackUtils::attack(Aggressive &attacker, Vulnerable &attacked, chtype ch) {
    if (attacked.defendVal > attacker.attackVal) {
        return true;
    }
    attacked.healthPoint -= attacker.attackVal - attacked.defendVal;
    Item &attackedItem = dynamic_cast<Item &>(attacked);
    chtype originCh = attackedItem.symbol;
    if (originCh != ch) {
        attackedItem.symbol = ch;
        MapUtils::updateAxis(attackedItem.xPos, attackedItem.yPos, &attackedItem);
    }
    if (attacked.healthPoint <= 0) {
        return false;
    } else {
        return true;
    }
}