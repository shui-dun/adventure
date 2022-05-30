#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "movable.hpp"

class Enemy : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Enemy(int x, int y) {
        xPos = x;
        yPos = y;
        symbol = 'O';
        healthPoint = 6;
        attackVal = 2;
        timeInterval = 200;
    }

    void move() override {
        int newX = xPos, newY = yPos;
        // A*搜索，尚待实现

    }

    bool beAttacked(Aggressive &attacker) override {
        return AttackUtils::attack(*this, attacker);
    }


};

#endif