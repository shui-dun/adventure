#ifndef POTION_HPP
#define POTION_HPP

#include "hero.hpp"
#include "random"
#include "item.hpp"

class Potion : public Item {
public:
    virtual void actOn(Hero hero) = 0;
};

class CurePotion : public Potion {
    int value;
public:
    CurePotion() {
        value = 3;
    }

    void actOn(Hero hero) {
        hero.healthPoint += value;
    }
};

class strengthenPotion : public Potion {
    int value;
public:
    strengthenPotion() {
        value = 1;
    }

    void actOn(Hero hero) {
        hero.attackVal += value;
    }
};

#endif