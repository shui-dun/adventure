#include "shooter.h"
#include "mixin.h"
#include "map.h"
#include "potion.h"
#include <thread>
#include <map>
#include <curses.h>

map<chtype, int> HeroShooter::directMap = {{'w', 0},
                                           {'s', 1},
                                           {'a', 2},
                                           {'d', 3}};


HeroShooter::HeroShooter(int xPos, int yPos)
        : Shooter(xPos, yPos, 'A', COLOR_PAIR(ME), 20, 1,
                  1, 1, PLAYER, 3, 0),
          score(0) {}

void HeroShooter::updateSymbol() {
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

bool HeroShooter::act() {
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
        auto bullet = new HeroBullet(bulletX, bulletY, *this);
        if (globalMap[bulletX][bulletY] == nullptr) {
            MapUtils::updateAxis(bulletX, bulletY, bullet);
            return true;
        } else {
            auto vulnerable = dynamic_cast<Vulnerable *>(globalMap[bulletX][bulletY]);
            if (vulnerable) {
                bullet->attack(*vulnerable);
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
    } else if (inputChar == 'c') {
        mindControl();
        return true;
    } else {
        return true;
    }
}

vector<Item *> HeroShooter::findNearestEnemies() {
    vector<Item *> v;
    for (int newX = xPos - 2; newX <= xPos + 2; newX++) {
        for (int newY = yPos - 2; newY <= yPos + 2; newY++) {
            if (!MapUtils::isAxisLegal(newX, newY))
                continue;
            auto item = globalMap[newX][newY];
            if (item == nullptr)
                continue;
            if (item->camp != camp && item->camp != OBJECT)
                v.push_back(item);
        }
    }
    return v;
}

void HeroShooter::mindControl() {
    for (auto enemy: findNearestEnemies()) {
        enemy->camp = camp;
        enemy->color = COLOR_PAIR(MIND_CONTROL);
        MapUtils::updateAxis(enemy->xPos, enemy->yPos, enemy);
    }
}


RandomWalkShooter::RandomWalkShooter(int xPos, int yPos)
        : Shooter(xPos, yPos,
                  'X', COLOR_PAIR(NORMAL_INIT),
                  6,
                  1,
                  6,
                  randEngine() % 6,
                  ENEMY,
                  3,
                  0) {}

bool RandomWalkShooter::act() {
    direction = uniform_int_distribution<int>(0, 3)(randEngine);
    auto p = MoveUtils::nextPosOfDirection(*this, direction);
    double choice = uniform_real_distribution<double>(0, 1)(randEngine);
    int newX = p.first, newY = p.second;
    if (choice < 0.5) {
        Item *item = globalMap[newX][newY];
        if (item == nullptr) {
            MoveUtils::moveToPos(*this, newX, newY);
            return true;
        } else {
            auto aggressive = dynamic_cast<Aggressive *>(item);
            if (aggressive) {
                return aggressive->attack(*this);
            } else {
                return true;
            }
        }
    } else {
        auto bullet = new NormalBullet(newX, newY, *this);
        if (globalMap[newX][newY] == nullptr) {
            MapUtils::updateAxis(newX, newY, bullet);
            return true;
        } else {
            auto vulnerable = dynamic_cast<Vulnerable *>(globalMap[newX][newY]);
            if (vulnerable) {
                bullet->attack(*vulnerable);
            }
            delete bullet;
            return true;
        }
    }
}
