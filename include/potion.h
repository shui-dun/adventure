#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H

#include "shooter.h"
#include "item.h"

class Potion : public Item {
public:
    Potion(int xPos, int yPos, chtype symbol, chtype color, CampEnum camp, int value)
            : Item(xPos, yPos, symbol, color,
                   camp), value(value) {}

    int value;

    virtual void actOn(HeroShooter &hero) = 0;
};

class CurePotion : public Potion {
public:
    CurePotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

class StrengthenPotion : public Potion {
public:
    StrengthenPotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

class DefendPotion : public Potion {
public:
    DefendPotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

class MindControlPotion : public Potion {
public:
    MindControlPotion(int xPos, int yPos);

    void actOn(HeroShooter &hero) override;
};

#endif //ADVENTURE_POTION_H
