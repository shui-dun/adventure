#include "swordsman.h"
#include "draw.h"
#include <random>
#include "archer.h"
#include "map.h"
#include "barrier.h"
#include "search.h"


RandomWalkSwordsman::RandomWalkSwordsman(int xPos, int yPos)
        : Swordsman(xPos, yPos, DrawUtils::SWORDSMAN_SYMBOL, COLOR_PAIR(DrawUtils::RANDOM_WALK_ENEMY),
                    6 + AttackUtils::healthPointGainOfEnemies(),
                    1 + AttackUtils::defendValGainOfEnemies(),
                    3 + AttackUtils::attackValGainOfEnemies(),
                    8, MapUtils::randEngine() % 6, ENEMY) {}

bool RandomWalkSwordsman::act() {
    uniform_int_distribution<int> distribution(0, 3);
    int direction = distribution(MapUtils::randEngine); // 找到一个随机的方向
    auto p = MapUtils::nextPosOfDirection(*this, direction);
    return SwordsmanUtils::defaultAction(this, p.first, p.second);
}

bool RandomWalkSwordsman::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) { // 不能攻击围墙
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}


SmartSwordsman::SmartSwordsman(int xPos, int yPos)
        : Swordsman(xPos, yPos, DrawUtils::SWORDSMAN_SYMBOL, COLOR_PAIR(DrawUtils::SMART_ENEMY),
                    6 + AttackUtils::healthPointGainOfEnemies(),
                    1 + AttackUtils::defendValGainOfEnemies(),
                    3 + AttackUtils::attackValGainOfEnemies(),
                    8, MapUtils::randEngine() % 8,
                    ENEMY) {}

bool SmartSwordsman::act() {
    pair<int, int> p;
    if (camp == ENEMY) {
        if (!MapUtils::myHero)
            return true;
        // 搜索玩家的位置
        p = AStar()(this, MapUtils::myHero);
    } else {
        // 搜索最近的敌人
        p = BFS()(this, [](Item *item) -> bool {
            return item->camp == ENEMY && !dynamic_cast<Arrow *>(item);
        }).second;
    }
    if (p.first == -1) {
        return true;
    }
    return SwordsmanUtils::defaultAction(this, p.first, p.second);
}

bool SmartSwordsman::attack(Vulnerable &vulnerable) {
    if (dynamic_cast<Barrier *>(&vulnerable)) { // 不能攻击围墙
        return true;
    } else {
        return AttackUtils::attack(*this, vulnerable);
    }
}

bool SwordsmanUtils::defaultAction(Swordsman *swordsman, int newX, int newY) {
    if (!MapUtils::gameMap[newX][newY]) { // 如果前方是空地，直接前进
        MapUtils::moveToPos(*swordsman, newX, newY);
        return true;
    } else if (dynamic_cast<Vulnerable *>(MapUtils::gameMap[newX][newY])) {
        // 如果前方的物品可以受到攻击，那么去攻击
        auto &attacked = dynamic_cast<Vulnerable &>(*MapUtils::gameMap[newX][newY]);
        bool aliveOfEnemy = swordsman->attack(attacked);
        if (aliveOfEnemy) {
            if (dynamic_cast<Aggressive *>(MapUtils::gameMap[newX][newY])) {
                // 如果对方被攻击后还存活，那么受到对方的攻击
                auto &aggressive = dynamic_cast<Aggressive &>(*MapUtils::gameMap[newX][newY]);
                return aggressive.attack(*swordsman);
            } else {
                return true;
            }
        } else { // 如果对方被攻击后死亡，那么前进一步
            MapUtils::moveToPos(*swordsman, newX, newY);
            return true;
        }
    } else if (dynamic_cast<Aggressive *>(MapUtils::gameMap[newX][newY])) {
        // 如果对方是可以攻击的，那么受到对方的攻击
        auto &aggressive = dynamic_cast<Aggressive &>(*MapUtils::gameMap[newX][newY]);
        return aggressive.attack(*swordsman);
    } else {
        return true;
    }
}
