#include "archer.h"
#include "draw.h"
#include "map.h"
#include "potion.h"
#include "astar.h"
#include <thread>
#include <random>
#include <map>
#include <cursesw.h>

map<chtype, int> HeroArcher::directMap = {{'w', 0},
                                          {'s', 1},
                                          {'a', 2},
                                          {'d', 3}};


HeroArcher::HeroArcher(int xPos, int yPos)
        : Archer(xPos, yPos, DrawUtils::HERO_SHOOTER_UP_SYMBOL, COLOR_PAIR(DrawUtils::HERO), 20, 1,
                 1, 1, PLAYER, 3, 0),
          score(0), nMindControl(0) {}

void HeroArcher::updateSymbol() {
    if (direction == 0) {
        symbol = DrawUtils::HERO_SHOOTER_UP_SYMBOL;
    } else if (direction == 1) {
        symbol = DrawUtils::HERO_SHOOTER_DOWN_SYMBOL;
    } else if (direction == 2) {
        symbol = DrawUtils::HERO_SHOOTER_LEFT_SYMBOL;
    } else if (direction == 3) {
        symbol = DrawUtils::HERO_SHOOTER_RIGHT_SYMBOL;
    }
}

bool HeroArcher::act() {
    int newX, newY;
    if (directMap.find(inputChar) != directMap.end()) {
        if (direction == directMap[inputChar]) {
            auto p = MapUtils::nextPosOfDirection(*this, direction);
            newX = p.first;
            newY = p.second;
            Item *item = MapUtils::gameMap[newX][newY];
            if (!item) {
                MapUtils::moveToPos(*this, newX, newY);
                return true;
            } else {
                auto potion = dynamic_cast<Potion *>(item);
                auto aggressive = dynamic_cast<Aggressive *>(item);
                if (potion) {
                    potion->actOn(*this);
                    MapUtils::moveToPos(*this, newX, newY);
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
            MapUtils::gameMap[xPos][yPos] = this;
            return true;
        }
    } else if (inputChar == ' ') {
        auto p = MapUtils::nextPosOfDirection(*this, direction);
        int bulletX = p.first, bulletY = p.second;
        auto bullet = new HeroArrow(bulletX, bulletY, *this);
        if (!MapUtils::gameMap[bulletX][bulletY]) {
            MapUtils::gameMap[bulletX][bulletY] = bullet;
            return true;
        } else {
            auto vulnerable = dynamic_cast<Vulnerable *>(MapUtils::gameMap[bulletX][bulletY]);
            if (vulnerable) {
                bullet->attack(*vulnerable);
            }
            delete bullet;
            return true;
        }
    } else if (inputChar == 'Q') {
        MapUtils::gameMap[xPos][yPos] = nullptr;
        delete this;
        MapUtils::gameOver = true;
        return false;
    } else if (inputChar == 'p') {
        DrawUtils::pause();
        return true;
    } else if (inputChar == 'c') {
        if (nMindControl > 0) {
            nMindControl--;
            mindControl();
        }
        return true;
    } else {
        return true;
    }
}

vector<Item *> HeroArcher::findNearestEnemies() {
    vector<Item *> v;
    for (int newX = xPos - 3; newX <= xPos + 3; newX++) {
        for (int newY = yPos - 3; newY <= yPos + 3; newY++) {
            if (!MapUtils::isAxisLegal(newX, newY))
                continue;
            auto item = MapUtils::gameMap[newX][newY];
            if (!item)
                continue;
            if (item->camp != camp && item->camp != OBJECT)
                v.push_back(item);
        }
    }
    return v;
}

void HeroArcher::mindControl() {
    for (auto enemy: findNearestEnemies()) {
        enemy->camp = camp;
        enemy->color = COLOR_PAIR(DrawUtils::MIND_CONTROL);
        MapUtils::gameMap[enemy->xPos][enemy->yPos] = enemy;
    }
}


RandomWalkArcher::RandomWalkArcher(int xPos, int yPos)
        : Archer(xPos, yPos,
                 DrawUtils::ENEMY_SHOOTER_SYMBOL, COLOR_PAIR(DrawUtils::RANDOM_WALK_ENEMY),
                  6 + AttackUtils::healthPointGainOfEnemies(),
                  1 + AttackUtils::defendValGainOfEnemies(),
                 6,
                  MapUtils::randEngine() % 6,
                 ENEMY,
                  3 + AttackUtils::attackValGainOfEnemies(),
                 0) {}

bool RandomWalkArcher::act() {
    direction = uniform_int_distribution<int>(0, 3)(MapUtils::randEngine);
    auto p = MapUtils::nextPosOfDirection(*this, direction);
    double choice = uniform_real_distribution<double>(0, 1)(MapUtils::randEngine);
    int newX = p.first, newY = p.second;
    if (choice < 0.5) {
        return ArcherUtils::defaultMove(this, newX, newY);
    } else {
        return ArcherUtils::defaultShoot(this, 0, 0);
    }
}

SmartArcher::SmartArcher(int xPos, int yPos)
        : Archer(xPos, yPos,
                 DrawUtils::ENEMY_SHOOTER_SYMBOL, COLOR_PAIR(DrawUtils::SMART_ENEMY),
                  6 + AttackUtils::healthPointGainOfEnemies(),
                  1 + AttackUtils::defendValGainOfEnemies(),
                 6,
                  MapUtils::randEngine() % 6,
                 ENEMY,
                  3 + AttackUtils::attackValGainOfEnemies(),
                 0) {}

bool SmartArcher::act() {
    Item &enemy = *MapUtils::myHero;
    if (aligned(enemy)) {
        direction = MapUtils::locatedAtDirection(*this, enemy.xPos, enemy.yPos);
        auto p = MapUtils::nextPosOfDirection(*this, direction);
        return ArcherUtils::defaultShoot(this, p.first, p.second);
    } else {
        auto p = AStar()(this, &enemy);
        if (p.first == -1)
            return true;
        direction = MapUtils::locatedAtDirection(*this, p.first, p.second);
        return ArcherUtils::defaultMove(this, p.first, p.second);
    }
}

bool SmartArcher::aligned(Item &item) {
    if (xPos == item.xPos) {
        int minY = min(yPos, item.yPos);
        int maxY = max(yPos, item.yPos);
        for (int y = minY + 1; y <= maxY - 1; ++y) {
            if (MapUtils::gameMap[xPos][y]) {
                return false;
            }
        }
        return true;
    }
    if (yPos == item.yPos) {
        int minX = min(xPos, item.xPos);
        int maxX = max(xPos, item.xPos);
        for (int x = minX + 1; x <= maxX - 1; ++x) {
            if (MapUtils::gameMap[x][yPos]) {
                return false;
            }
        }
        return true;
    }
    return false;
}


bool ArcherUtils::defaultMove(Archer *shooter, int newX, int newY) {
    Item *item = MapUtils::gameMap[newX][newY];
    if (!item) {
        MapUtils::moveToPos(*shooter, newX, newY);
        return true;
    } else {
        auto aggressive = dynamic_cast<Aggressive *>(item);
        if (aggressive) {
            return aggressive->attack(*shooter);
        } else {
            return true;
        }
    }
}

bool ArcherUtils::defaultShoot(Archer *shooter, int newX, int newY) {
    auto bullet = new NormalArrow(newX, newY, *shooter);
    if (!MapUtils::gameMap[newX][newY]) {
        MapUtils::gameMap[newX][newY] = bullet;
        return true;
    } else {
        auto vulnerable = dynamic_cast<Vulnerable *>(MapUtils::gameMap[newX][newY]);
        if (vulnerable) {
            bullet->attack(*vulnerable);
        }
        delete bullet;
        return true;
    }
}
