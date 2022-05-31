#include "attack.h"
#include "item.h"

bool AttackUtils::attack(Aggressive &attacker, Vulnerable &attacked, chtype ch) {
    attacked.healthPoint -= attacker.attackVal;
    dynamic_cast<Item &>(attacked).symbol = ch;
    if (attacked.healthPoint <= 0) {
        return false;
    } else {
        return true;
    }
}