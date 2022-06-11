#ifndef ADVENTURE_ARCHER_H
#define ADVENTURE_ARCHER_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include <map>
#include <vector>

using namespace std;

/**
 * 弓箭手，弓箭手可以发射箭矢攻击敌人
 */
class Archer : public Item, public Vulnerable, public Movable {
public:

    /** 箭矢的攻击值 */
    int arrowAttackVal;

    /** 移动或发射箭矢时的方向 */
    int direction;

    Archer(int xPos, int yPos, const char *symbol, chtype color, int healthPoint, int defendVal,
           unsigned int timeUnits, unsigned int curTimeUnit,
           CampEnum camp,
           int bulletAttackVal, int direction) :
            Item(xPos, yPos, symbol, color, camp),
            Vulnerable(healthPoint, defendVal),
            Movable(timeUnits, curTimeUnit),
            arrowAttackVal(bulletAttackVal), direction(direction) {}
};


/**
 * 玩家，玩家是一种弓箭手
 */
class HeroArcher : public Archer {
private:
    /** 根据玩家当前的方向更新显示的字符 */
    void updateSymbol();

    /** 将玩家输入的字母（wsad）映射为对应的方向 */
    static map<chtype, int> directMap;

    /**
     * 找到玩家半径3单位内的敌人，该方法在精神控制药水发动时被调用
     * @return 找到的敌人的向量
     */
    vector<Item *> findNearestEnemies();

    /** 发动精神药水 */
    void mindControl();

    /** 射箭 */
    void shoot();

public:

    /** 玩家输入的字符 */
    chtype inputChar;

    /** 分数 */
    int score;

    /** 精神控制药水的数目 */
    int nMindControl;

    HeroArcher(int xPos, int yPos);

    bool act() override;
};

/**
 * 随机游走的弓箭手，随机在地图中游走
 */
class RandomWalkArcher : public Archer {
public:
    RandomWalkArcher(int xPos, int yPos);

    bool act() override;
};

/**
 * 智能弓箭手，追踪敌人位置，当与敌人处于一条直线并且中间没有障碍物时会射箭攻击敌人
 */
class SmartArcher : public Archer {
private:
    /**
     * 判断是否与指定的物品对齐
     * @param item 指定的物品
     * @return 是否对齐
     */
    bool aligned(Item &item);

public:
    SmartArcher(int xPos, int yPos);

    bool act() override;
};

/**
 * 弓箭手工具类
 */
class ArcherUtils {
public:
    /**
     * 默认的移动效果
     * @param archer 弓箭手
     * @param newX 移动后的新位置的x坐标
     * @param newY 移动后的新位置的y坐标
     * @return 移动后该弓箭手是否仍然存活
     */
    static bool defaultMove(Archer *archer, int newX, int newY);

    /**
     * 默认的射击效果
     * @param archer 弓箭手
     * @param newX 发射出的箭矢的位置的x坐标
     * @param newY 发射出的箭矢的位置的y坐标
     * @return 射击后该弓箭手是否仍然存活
     */
    static bool defaultShoot(Archer *archer, int newX, int newY);
};

#endif //ADVENTURE_ARCHER_H
