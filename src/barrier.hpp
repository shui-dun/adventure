#ifndef BARRIER_HPP
#define BARRIER_HPP

#include "item.hpp"
#include "attack.hpp"

class SolidBarrier : public Item {
public:

    SolidBarrier(int x, int y) {
        xPos = x;
        yPos = y;
        symbol = '*';
    }
};

class WeakBarrier : public Item, public Vulnerable {
public:

    WeakBarrier(int x, int y) {
        xPos = x;
        yPos = y;
        symbol = '#';
        healthPoint = 10;
    }

    bool beAttacked(Aggressive &attacker) override {
        return AttackUtils::attack(*this, attacker);
    }
};

#endif