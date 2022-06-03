#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H

#include "shooter.h"
#include "item.h"

class Potion : public Item {
public:
    Potion(int xPos, int yPos, chtype symbol, CampEnum camp) : Item(xPos, yPos, symbol, camp) {}

    virtual void actOn(Shooter &hero) = 0;
};

class CurePotion : public Potion {
    int value;
public:
    CurePotion(int xPos, int yPos);

    void actOn(Shooter &hero) override;
};

class StrengthenPotion : public Potion {
    int value;
public:
    StrengthenPotion(int xPos, int yPos);

    void actOn(Shooter &hero) override;
};

class DefendPotion : public Potion {
    int value;
public:
    DefendPotion(int xPos, int yPos);

    void actOn(Shooter &hero) override;
};

#endif //ADVENTURE_POTION_H
