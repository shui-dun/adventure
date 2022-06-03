#include "shooter.h"
#include "mixin.h"
#include "map.h"
#include "potion.h"
#include <thread>
#include <map>

map<chtype, int> Shooter::directMap = {{'w', 0},
                                       {'s', 1},
                                       {'a', 2},
                                       {'d', 3}};

Shooter::Shooter(int xPos, int yPos)
        : Item(xPos, yPos, 'A' | COLOR_PAIR(ME), PLAYER),
          Vulnerable(20, 1, 0),
          Movable(2, 1),
          bulletAttackVal(3), direction(0), score(0) {}

void Shooter::updateSymbol() {
    if (direction == 0) {
        symbol = 'A' | COLOR_PAIR(ME);
    } else if (direction == 1) {
        symbol = 'V' | COLOR_PAIR(ME);
    } else if (direction == 2) {
        symbol = '<' | COLOR_PAIR(ME);
    } else if (direction == 3) {
        symbol = '>' | COLOR_PAIR(ME);
    }
}

bool Shooter::act() {
    int newX, newY;
    if (directMap.find(inputChar) != directMap.end()) {
        if (direction == directMap[inputChar]) {
            auto p = MoveUtils::nextPosOfDirection(*this, direction);
            newX = p.first;
            newY = p.second;
            Item *item = globalMap[newX][newY];
            if (item == nullptr) {
                MoveUtils::moveToPos(*this, newX, newY);
                return true;
            } else {
                auto potion = dynamic_cast<Potion *>(item);
                auto aggressive = dynamic_cast<Aggressive *>(item);
                if (potion) {
                    potion->actOn(*this);
                    MoveUtils::moveToPos(*this, newX, newY);
                    return true;
                } else if (aggressive) {
                    return aggressive->attack(*this);
                } else {
                    return true;
                }
            }
        } else {
            direction = directMap[inputChar];
            updateSymbol();
            MapUtils::updateAxis(xPos, yPos, this);
            return true;
        }
    } else if (inputChar == ' ') {
        auto p = MoveUtils::nextPosOfDirection(*this, direction);
        int bulletX = p.first, bulletY = p.second;
        auto bullet = new Bullet(bulletX, bulletY, direction, bulletAttackVal, *this, this->camp);
        if (globalMap[bulletX][bulletY] == nullptr) {
            MapUtils::updateAxis(bulletX, bulletY, bullet);
            return true;
        } else {
            if (dynamic_cast<Vulnerable *>(globalMap[bulletX][bulletY])) {
                bullet->attack(dynamic_cast<Vulnerable &>(*globalMap[bulletX][bulletY]));
            }
            delete bullet;
            return true;
        }
    } else if (inputChar == 'Q') {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        delete this;
        gameOver = true;
        return false;
    } else if (inputChar == 'p') {
        MapUtils::pause();
        return true;
    } else {
        return true;
    }
}


