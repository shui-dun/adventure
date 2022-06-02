#include "hero.h"
#include "mixin.h"
#include "map.h"
#include "potion.h"
#include <thread>
#include <map>

map<chtype, int> Hero::directMap = {{'w', 0},
                                    {'s', 1},
                                    {'a', 2},
                                    {'d', 3}};

void Hero::updateSymbol() {
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


Hero::Hero(int x, int y) {
    xPos = x;
    yPos = y;
    symbol = 'A' | COLOR_PAIR(ME);
    healthPoint = 20;
    timeUnits = 2;
    curTimeUnit = randEngine() % timeUnits;
    direction = 0;
    score = 0;
}

bool Hero::move() {
    chtype ch = getch();
    mapMutex.lock();
    int newX, newY;
    if (directMap.find(ch) != directMap.end()) {
        if (direction == directMap[ch]) {
            auto p = MoveUtils::moveWithDirection(*this, direction);
            newX = p.first;
            newY = p.second;
        } else {
            direction = directMap[ch];
            updateSymbol();
            MapUtils::updateAxis(xPos, yPos, this);
            return true;
        }
    } else if (ch == ' ') {
        auto bullet = new Bullet(xPos, yPos, direction, bulletAttackVal);
        auto p = MoveUtils::moveWithDirection(*bullet, direction);
        int bulletX = p.first, bulletY = p.second;
        if (globalMap[bulletX][bulletY] == nullptr) {
            bullet->xPos = bulletX;
            bullet->yPos = bulletY;
            bullet->direction = direction;
            MapUtils::updateAxis(bulletX, bulletY, bullet);
            return true;
        } else {
            delete bullet;
            return true;
        }
    } else if (ch == 'Q') {
        return false;
    } else {
        return true;
    }
    updateSymbol();
    Item *item = globalMap[newX][newY];
    if (item == nullptr) {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        MapUtils::updateAxis(newX, newY, this);
        xPos = newX;
        yPos = newY;
        return true;
    } else {
        auto aggressive = dynamic_cast<Aggressive *>(item);
        auto potion = dynamic_cast<Potion *>(item);
        if (potion) {
            potion->actOn(*this);
            MapUtils::updateAxis(xPos, yPos, nullptr);
            if (healthPoint > 0) {
                MapUtils::updateAxis(newX, newY, this);
                xPos = newX;
                yPos = newY;
                return true;
            } else {
                return false;
            }
        } else if (aggressive) {
            if (!beAttacked(*aggressive)) {
                MapUtils::updateAxis(xPos, yPos, nullptr);
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }
}

bool Hero::beAttacked(Aggressive &attacker) {
    return AttackUtils::attack(attacker, *this, this->symbol);
}

bool Hero::shouldIMove() {
    return MoveUtils::defaultShouldIMove(*this);
}

