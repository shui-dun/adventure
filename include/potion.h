#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H

#include "hero.h"
#include "item.h"

class Potion : public Item {
public:
    Potion(int xPos, int yPos, chtype symbol) : Item(xPos, yPos, symbol) {}

    virtual void actOn(Hero &hero) = 0;
};

class CurePotion : public Potion {
    int value;
public:
    CurePotion(int xPos, int yPos);

    void actOn(Hero &hero) override;
};

class StrengthenPotion : public Potion {
    int value;
public:
    StrengthenPotion(int xPos, int yPos);

    void actOn(Hero &hero) override;
};

class DefendPotion : public Potion {
    int value;
public:
    DefendPotion(int xPos, int yPos);

    void actOn(Hero &hero) override;
};

#endif //ADVENTURE_POTION_H
