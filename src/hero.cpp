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


Hero::Hero(int xPos, int yPos)
        : Item(xPos, yPos, 'A' | COLOR_PAIR(ME)),
          Vulnerable(20, 1),
          Movable(2, 1),
          bulletAttackVal(3), direction(0), score(0) {}

bool Hero::move() {
    int newX, newY;
    if (directMap.find(inputChar) != directMap.end()) {
        if (direction == directMap[inputChar]) {
            auto p = MoveUtils::moveWithDirection(*this, direction);
            newX = p.first;
            newY = p.second;
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
                        MapUtils::updateAxis(newX, newY, nullptr);
                        gameOver = true;
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
        } else {
            direction = directMap[inputChar];
            updateSymbol();
            MapUtils::updateAxis(xPos, yPos, this);
            return true;
        }
    } else if (inputChar == ' ') {
        auto p = MoveUtils::moveWithDirection(*this, direction);
        int bulletX = p.first, bulletY = p.second;
        auto bullet = new Bullet(bulletX, bulletY, direction, bulletAttackVal, *this);
        if (globalMap[bulletX][bulletY] == nullptr) {
            MapUtils::updateAxis(bulletX, bulletY, bullet);
            return true;
        } else {
            bullet->attack(globalMap[bulletX][bulletY]);
            delete bullet;
            return true;
        }
    } else if (inputChar == 'Q') {
        MapUtils::updateAxis(xPos, yPos, nullptr);
        gameOver = true;
        return false;
    } else if (inputChar == 'p') {
        mvprintw(MapUtils::lines - 1, 1,
                 "Game Paused, Press p to Continue                               ");
        refresh();
        while (getch() != 'p') {
        }
        mvprintw(MapUtils::lines - 1, 1,
                 "                                                               ");
        refresh();
        return true;
    } else {
        return true;
    }
}

bool Hero::beAttacked(Aggressive &attacker) {
    bool alive = AttackUtils::attack(attacker, *this, this->symbol);
    if (!alive) {
        gameOver = true;
        return false;
    } else {
        return true;
    }
}

bool Hero::shouldIMove() {
    return true;
}

