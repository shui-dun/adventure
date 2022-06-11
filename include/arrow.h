#ifndef ADVENTURE_ARROW_H
#define ADVENTURE_ARROW_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include "map.h"
#include "archer.h"

/**
 * 箭矢
 */
class Arrow : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Arrow(int xPos, int yPos, const char *symbol, chtype color, CampEnum camp, unsigned int timeUnits,
          unsigned int curTimeUnit,
          int healthPoint, int defendVal, int attackVal, int direction)
            : Item(xPos, yPos, symbol, color, camp),
              Movable(timeUnits, curTimeUnit),
              Vulnerable(healthPoint, defendVal),
              Aggressive(attackVal),
              direction(direction) {}

    // 前进方向
    int direction;
};


/**
 * 普通的箭矢
 */
class NormalArrow : public Arrow {
public:
    NormalArrow(int xPos, int yPos, Archer &launcher);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;

};

/**
 * 玩家发动的箭矢，和普通箭矢的区别在于该箭矢造成的伤害可以为玩家增加得分
 */
class HeroArrow : public Arrow {
public:
    HeroArrow(int xPos, int yPos, HeroArcher &launcher);

    /** 发动者 */
    HeroArcher &launcher;

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;
};

/**
 * 箭矢工具类
 */
class ArrowUtils {
public:
    /** 箭矢的默认行为 */
    static bool defaultAction(Arrow &arrow);
};

#endif //ADVENTURE_ARROW_H
