#ifndef BULLET_HPP
#define BULLET_HPP

#include "movable.hpp"
#include "attack.hpp"
#include "map.hpp"
#include <utility>
using namespace std;

class Bullet : public Item, public Movable, public Vulnerable, public Aggressive {
    int direction;
public:
    Bullet(int x, int y, int direction) {
        xPos = x;
        yPos = y;
        symbol = 'x';
        healthPoint = 1;
        attackVal = 2;
        timeInterval = 200;
        this->direction = direction;
    }

    void move() override {
        int newX = xPos, newY = yPos;
        if (direction == 0) {
            newY -= 1;
        } else if (direction == 1) {
            newY += 1;
        } else if (direction == 2) {
            newX -= 1;
        } else {
            newX += 1;
        }
        if (globalMap.items[newX][newY] == nullptr) {
            globalMap.items[xPos][yPos] = nullptr;
            globalMap.items[newX][newY] = this;
            // 记得这里画图
        } else {
            globalMap.items[xPos][yPos] = nullptr;
            Item *impacted = globalMap.items[newX][newY];
            if (dynamic_cast<Vulnerable *>(impacted)) {
                auto vulnerableImpacted = dynamic_cast<Vulnerable *>(impacted);
                if (!vulnerableImpacted->beAttacked(*this)) {
                    delete impacted;
                    globalMap.items[newX][newY] = nullptr;
                    // 记得这里画图
                }
            }
        }
    }

    bool beAttacked(Aggressive &attacker) override {
        return false;
    }
};

#endif