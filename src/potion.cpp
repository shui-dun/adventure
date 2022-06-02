#include "potion.h"
#include "mixin.h"

CurePotion::CurePotion(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = '+' | COLOR_PAIR(POTION);
    value = 3;
}

void CurePotion::actOn(Hero &hero) {
    hero.healthPoint += value;
}

StrengthenPotion::StrengthenPotion(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = '!' | COLOR_PAIR(POTION);
    value = 1;
}

void StrengthenPotion::actOn(Hero &hero) {
    hero.bulletAttackVal += value;
}

DefendPotion::DefendPotion(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = 'U' | COLOR_PAIR(POTION);
    value = 1;
}

void DefendPotion::actOn(Hero &hero) {
    hero.defendVal += value;
}
