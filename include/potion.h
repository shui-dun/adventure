#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H

#include "archer.h"
#include "item.h"

class Potion : public Item {
public:
    Potion(int xPos, int yPos, const char *symbol, chtype color, CampEnum camp, int value)
            : Item(xPos, yPos, symbol, color,
                   camp), value(value) {}

    int value;

    virtual void actOn(HeroArcher &hero) = 0;
};

class CurePotion : public Potion {
public:
    CurePotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

class StrengthenPotion : public Potion {
public:
    StrengthenPotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

class DefendPotion : public Potion {
public:
    DefendPotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

class MindControlPotion : public Potion {
public:
    MindControlPotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

#endif //ADVENTURE_POTION_H
