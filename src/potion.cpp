#include "potion.h"
#include "map.h"

CurePotion::CurePotion(int xPos, int yPos)
        : Potion(xPos, yPos, MapUtils::CURE_POTION_SYMBOL, COLOR_PAIR(MapUtils::POTION), OBJECT, 3) {}

void CurePotion::actOn(HeroShooter &hero) {
    hero.healthPoint += value;
}

StrengthenPotion::StrengthenPotion(int xPos, int yPos)
        : Potion(xPos, yPos, MapUtils::STRENGTH_POTION_SYMBOL, COLOR_PAIR(MapUtils::POTION), OBJECT, 1) {}

void StrengthenPotion::actOn(HeroShooter &hero) {
    hero.bulletAttackVal += value;
}

DefendPotion::DefendPotion(int xPos, int yPos)
        : Potion(xPos, yPos, MapUtils::DEFEND_POTION_SYMBOL, COLOR_PAIR(MapUtils::POTION), OBJECT, 1) {}

void DefendPotion::actOn(HeroShooter &hero) {
    hero.defendVal += value;
}

MindControlPotion::MindControlPotion(int xPos, int yPos)
        : Potion(xPos, yPos, MapUtils::MIND_CONTROL_POTION_SYMBOL, COLOR_PAIR(MapUtils::POTION), OBJECT, 1) {}

void MindControlPotion::actOn(HeroShooter &hero) {
    hero.nMindControl += value;
}
