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
    if (attacked.healthPoint <= attacked.initHealthPoint / 2 && attacked.injuredSymbol != 0) {
        attackedItem.symbol = attacked.injuredSymbol;
        MapUtils::updateAxis(attackedItem.xPos, attackedItem.yPos, &attackedItem);
    }
    if (attacked.healthPoint <= 0) {
        if (dynamic_cast<Hero *>(&attacked)) {
            gameOver = true;
        }
        MapUtils::updateAxis(attackedItem.xPos, attackedItem.yPos, nullptr);
        delete &attacked;
        return false;
    } else {
        return true;
    }
}