#include "potion.h"
#include "mixin.h"

CurePotion::CurePotion(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = '+' | COLOR_PAIR(CURE_POTION);
    value = 3;
}

void CurePotion::actOn(Hero hero) {
    hero.healthPoint += value;
}

StrengthenPotion::StrengthenPotion(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = '!' | COLOR_PAIR(STRENGTHEN_POTION);
    value = 1;
}

void StrengthenPotion::actOn(Hero hero) {
    hero.attackVal += value;
}
