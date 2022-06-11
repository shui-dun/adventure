#ifndef ADVENTURE_SWORDSMAN_H
#define ADVENTURE_SWORDSMAN_H

#include "move.h"
#include "attack.h"
#include "item.h"

/**
 * 剑士
 * 触碰到剑士的角色将受到伤害
 */
class Swordsman : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Swordsman(int xPos, int yPos, const char *symbol, chtype color, int healthPoint, int defendVal,
              int attackVal, unsigned int timeUnits, unsigned int curTimeUnit,
              CampEnum camp) :
            Item(xPos, yPos, symbol, color, camp),
            Vulnerable(healthPoint, defendVal),
            Aggressive(attackVal),
            Movable(timeUnits, curTimeUnit) {}
};

/**
 * 随机游走的剑士
 * 该剑士在地图中随机游走
 */
class RandomWalkSwordsman : public Swordsman {
public:
    RandomWalkSwordsman(int xPos, int yPos);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;
};

/**
 * 智能的剑士
 * 该剑士追踪敌人
 */
class SmartSwordsman : public Swordsman {
public:
    SmartSwordsman(int xPos, int yPos);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;

};

/**
 * 剑士工具类
 */
class SwordsmanUtils {
public:

    /**
     * 剑士默认的行动策略
     * @param swordsman 剑士
     * @param newX 目标位置的x坐标
     * @param newY 目标位置的x坐标
     * @return 剑士在行动后是否存活
     */
    static bool defaultAction(Swordsman *swordsman, int newX, int newY);
};

#endif //ADVENTURE_SWORDSMAN_H
