#include "archer.h"
#include "draw.h"
#include "map.h"
#include "potion.h"
#include "search.h"
#include <thread>
#include <random>
#include <map>
#include <cursesw.h>

map<chtype, int> HeroArcher::directMap = {{'w', 0},
                                          {'s', 1},
                                          {'a', 2},
                                          {'d', 3}};


HeroArcher::HeroArcher(int xPos, int yPos)
        : Archer(xPos, yPos, DrawUtils::HERO_ARCHER_UP_SYMBOL, COLOR_PAIR(DrawUtils::HERO), 20, 1,
                 1, 1, PLAYER, 3, 0),
          score(0), nMindControl(0) {}

void HeroArcher::updateSymbol() {
    if (direction == 0) {
        symbol = DrawUtils::HERO_ARCHER_UP_SYMBOL;
    } else if (direction == 1) {
        symbol = DrawUtils::HERO_ARCHER_DOWN_SYMBOL;
    } else if (direction == 2) {
        symbol = DrawUtils::HERO_ARCHER_LEFT_SYMBOL;
    } else if (direction == 3) {
        symbol = DrawUtils::HERO_ARCHER_RIGHT_SYMBOL;
    }
}

bool HeroArcher::act() {
    int newX, newY;
    if (directMap.find(inputChar) != directMap.end()) { // 如果输入的是调整方向的字符
        if (direction == directMap[inputChar]) { // 如果键入的方向与当前方向相同，那么就前进
            auto p = MapUtils::nextPosOfDirection(*this, direction);
            newX = p.first;
            newY = p.second;
            Item *item = MapUtils::gameMap[newX][newY];
            if (!item) { // 如果前方是空白，直接前进
                MapUtils::moveToPos(*this, newX, newY);
                return true;
            } else {
                auto potion = dynamic_cast<Potion *>(item);
                auto aggressive = dynamic_cast<Aggressive *>(item);
                if (potion) { // 如果是药水，那么作用药水的效果
                    potion->actOn(*this);
                    MapUtils::moveToPos(*this, newX, newY);
                    return true;
                } else if (aggressive) { // 如果是可攻击者，那么被攻击
                    return aggressive->attack(*this);
                } else {
                    return true;
                }
            }
        } else { // 如果键入的方向与当前方向不同，那么就改变方向
            direction = directMap[inputChar];
            updateSymbol();
            MapUtils::gameMap[xPos][yPos] = this;
            return true;
        }
    } else if (inputChar == ' ') { // 发射子弹
        shoot();
        return true;
    } else if (inputChar == 'Q') { // 退出游戏
        MapUtils::gameMap[xPos][yPos] = nullptr;
        MapUtils::myHero = nullptr;
        delete this;
        MapUtils::gameOver = true;
        return false;
    } else if (inputChar == 'p') { // 暂停游戏
        DrawUtils::pause();
        return true;
    } else if (inputChar == 'c') { // 发动精神控制
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
        auto v = dynamic_cast<Vulnerable *>(enemy);
        if (v) {
            v->healthPoint = v->initHealthPoint;
        }
        MapUtils::gameMap[enemy->xPos][enemy->yPos] = enemy;
    }
}

void HeroArcher::shoot() {
    auto p = MapUtils::nextPosOfDirection(*this, direction);
    int bulletX = p.first, bulletY = p.second;
    auto bullet = new HeroArrow(bulletX, bulletY, *this);
    if (!MapUtils::gameMap[bulletX][bulletY]) { // 如何前方是空地，释放子弹
        MapUtils::gameMap[bulletX][bulletY] = bullet;
        return;
    } else { // 否则直接用子弹攻击前方物体
        auto vulnerable = dynamic_cast<Vulnerable *>(MapUtils::gameMap[bulletX][bulletY]);
        if (vulnerable) {
            bullet->attack(*vulnerable);
        }
        delete bullet;
        return;
    }
}


RandomWalkArcher::RandomWalkArcher(int xPos, int yPos)
        : Archer(xPos, yPos,
                 DrawUtils::ENEMY_ARCHER_SYMBOL, COLOR_PAIR(DrawUtils::RANDOM_WALK_ENEMY),
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
        return ArcherUtils::defaultShoot(this, newX, newY);
    }
}

SmartArcher::SmartArcher(int xPos, int yPos)
        : Archer(xPos, yPos,
                 DrawUtils::ENEMY_ARCHER_SYMBOL, COLOR_PAIR(DrawUtils::SMART_ENEMY),
                 6 + AttackUtils::healthPointGainOfEnemies(),
                 1 + AttackUtils::defendValGainOfEnemies(),
                 6,
                 MapUtils::randEngine() % 6,
                 ENEMY,
                 3 + AttackUtils::attackValGainOfEnemies(),
                 0) {}

bool SmartArcher::act() {
    if (camp == ENEMY) { // 如果是ENEMY阵营
        Item *enemy = MapUtils::myHero;
        if (!enemy) {
            return true;
        }
        if (aligned(*enemy)) { // 如果与敌人对齐并且中间没有障碍物阻隔，直接射击
            direction = MapUtils::locatedAtDirection(*this, enemy->xPos, enemy->yPos);
            auto p = MapUtils::nextPosOfDirection(*this, direction);
            return ArcherUtils::defaultShoot(this, p.first, p.second);
        } else { // 否则使用A*算法搜索，进行移动
            auto p = AStar()(this, enemy);
            if (p.first == -1)
                return true;
            direction = MapUtils::locatedAtDirection(*this, p.first, p.second);
            return ArcherUtils::defaultMove(this, p.first, p.second);
        }
    } else { // 否则，使用BFS算法搜索最近的一个敌人
        auto pr = BFS()(this, [](Item *item) -> bool {
            return item->camp == ENEMY && !dynamic_cast<Arrow *>(item);
        });
        Item *enemy = pr.first;
        if (!enemy) {
            return true;
        }
        if (aligned(*enemy)) { // 如果与敌人对齐并且中间没有障碍物阻隔，直接射击
            direction = MapUtils::locatedAtDirection(*this, enemy->xPos, enemy->yPos);
            auto p = MapUtils::nextPosOfDirection(*this, direction);
            return ArcherUtils::defaultShoot(this, p.first, p.second);
        } else { // 否则靠近敌人
            auto p = pr.second;
            direction = MapUtils::locatedAtDirection(*this, p.first, p.second);
            return ArcherUtils::defaultMove(this, p.first, p.second);
        }
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


bool ArcherUtils::defaultMove(Archer *archer, int newX, int newY) {
    Item *item = MapUtils::gameMap[newX][newY];
    if (!item) { // 如果前方是空地，直接前进
        MapUtils::moveToPos(*archer, newX, newY);
        return true;
    } else { // 否则被攻击
        auto aggressive = dynamic_cast<Aggressive *>(item);
        if (aggressive) {
            return aggressive->attack(*archer);
        } else {
            return true;
        }
    }
}

bool ArcherUtils::defaultShoot(Archer *archer, int newX, int newY) {
    auto bullet = new NormalArrow(newX, newY, *archer);
    if (!MapUtils::gameMap[newX][newY]) {  // 如何前方是空地，释放子弹
        MapUtils::gameMap[newX][newY] = bullet;
        return true;
    } else {  // 否则直接用子弹攻击前方物体
        auto vulnerable = dynamic_cast<Vulnerable *>(MapUtils::gameMap[newX][newY]);
        if (vulnerable) {
            bullet->attack(*vulnerable);
        }
        delete bullet;
        return true;
    }
}
