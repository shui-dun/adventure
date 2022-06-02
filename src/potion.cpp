#include "potion.h"
#include "mixin.h"

CurePotion::CurePotion(int xPos, int yPos)
        : Potion(xPos, yPos, '+' | COLOR_PAIR(POTION)), value(3) {}

void CurePotion::actOn(Hero &hero) {
    hero.healthPoint += value;
}

StrengthenPotion::StrengthenPotion(int xPos, int yPos)
        : Potion(xPos, yPos, '!' | COLOR_PAIR(POTION)), value(1) {}

void StrengthenPotion::actOn(Hero &hero) {
    hero.bulletAttackVal += value;
}

DefendPotion::DefendPotion(int xPos, int yPos)
        : Potion(xPos, yPos, 'U' | COLOR_PAIR(POTION)), value(1) {}

void DefendPotion::actOn(Hero &hero) {
    hero.defendVal += value;
}
