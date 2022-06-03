#include "potion.h"
#include "mixin.h"

CurePotion::CurePotion(int xPos, int yPos)
        : Potion(xPos, yPos, '+' | COLOR_PAIR(POTION), OBJECT), value(3) {}

void CurePotion::actOn(Shooter &hero) {
    hero.healthPoint += value;
}

StrengthenPotion::StrengthenPotion(int xPos, int yPos)
        : Potion(xPos, yPos, '!' | COLOR_PAIR(POTION), OBJECT), value(1) {}

void StrengthenPotion::actOn(Shooter &hero) {
    hero.bulletAttackVal += value;
}

DefendPotion::DefendPotion(int xPos, int yPos)
        : Potion(xPos, yPos, 'U' | COLOR_PAIR(POTION), OBJECT), value(1) {}

void DefendPotion::actOn(Shooter &hero) {
    hero.defendVal += value;
}
