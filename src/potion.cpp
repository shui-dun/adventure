#include "potion.h"
#include "map.h"
#include "draw.h"

CurePotion::CurePotion(int xPos, int yPos)
        : Potion(xPos, yPos, DrawUtils::CURE_POTION_SYMBOL, COLOR_PAIR(DrawUtils::POTION), OBJECT, 3) {}

void CurePotion::actOn(HeroArcher &hero) {
    hero.healthPoint += value;
}

StrengthenPotion::StrengthenPotion(int xPos, int yPos)
        : Potion(xPos, yPos, DrawUtils::STRENGTH_POTION_SYMBOL, COLOR_PAIR(DrawUtils::POTION), OBJECT, 1) {}

void StrengthenPotion::actOn(HeroArcher &hero) {
    hero.arrowAttackVal += value;
}

DefendPotion::DefendPotion(int xPos, int yPos)
        : Potion(xPos, yPos, DrawUtils::DEFEND_POTION_SYMBOL, COLOR_PAIR(DrawUtils::POTION), OBJECT, 1) {}

void DefendPotion::actOn(HeroArcher &hero) {
    hero.defendVal += value;
}

MindControlPotion::MindControlPotion(int xPos, int yPos)
        : Potion(xPos, yPos, DrawUtils::MIND_CONTROL_POTION_SYMBOL, COLOR_PAIR(DrawUtils::POTION), OBJECT, 1) {}

void MindControlPotion::actOn(HeroArcher &hero) {
    hero.nMindControl += value;
}
