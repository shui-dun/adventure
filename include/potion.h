#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H

#include "shooter.h"
#include "item.h"

class Potion : public Item {
public:
    Potion(int xPos, int yPos, chtype symbol, chtype color, CampEnum camp) : Item(xPos, yPos, symbol, color, camp) {}

    virtual void actOn(HeroShooter &hero) = 0;
};

class CurePotion : public Potion {
    int value;
public:
    CurePotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

class StrengthenPotion : public Potion {
    int value;
public:
    StrengthenPotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

class DefendPotion : public Potion {
    int value;
public:
    DefendPotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

#endif //ADVENTURE_POTION_H
