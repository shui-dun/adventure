#ifndef HERO_HPP
#define HERO_HPP

#include "movable.hpp"

class Hero : public Item, public Aggressive, public Vulnerable, public Movable {
public:
    Hero(int x, int y) {
        xPos = x;
        yPos = y;
        symbol = 'M';
        attackVal = 2;
        healthPoint = 20;
        timeInterval = 0; // 不等待
    }

    void move() override {
        // 按照用户输入
    }

    bool beAttacked(Aggressive &attacker) override {
        return AttackUtils::attack(*this, attacker);
    }
};

#endif