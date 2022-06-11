#ifndef ADVENTURE_ATTACK_H
#define ADVENTURE_ATTACK_H

#include <cursesw.h>

/**
 * 可以受到攻击者
 */
class Vulnerable {
public:
    Vulnerable(int healthPoint, int defendVal)
            : healthPoint(healthPoint), defendVal(defendVal),
              initHealthPoint(healthPoint) {}

    virtual ~Vulnerable() = default;

    /** 血量 */
    int healthPoint;

    /** 初始血量 */
    int initHealthPoint;

    /** 防御值 */
    int defendVal;
};

/**
 * 好斗的，即别人接触到它它就会发动攻击
 */
class Aggressive {
public:
    Aggressive(int attackVal) : attackVal(attackVal) {}

    virtual ~Aggressive() = default;

    /** 攻击值 */
    int attackVal;

    /**
     * 攻击行为
     * @param vulnerable 被攻击者
     * @return 被攻击者在遭受攻击后是否存活
     */
    virtual bool attack(Vulnerable &vulnerable) = 0;
};

/**
 * 攻击工具类
 */
class AttackUtils {
public:

    /**
     * 使用指定攻击值攻击被攻击者的默认行为
     * @param attackVal 攻击值
     * @param attacked 受攻击者
     * @return 被攻击者是否存活
     */
    static bool attack(int attackVal, Vulnerable &attacked);

    /**
     * 攻击者攻击被攻击者的默认行为
     * @param attacker 攻击者
     * @param attacked 被攻击者
     * @return 被攻击者是否存活
     */
    static bool attack(Aggressive &attacker, Vulnerable &attacked);

    /**
     * 新生成的敌人的能力值由两部分组成
     * 一个是基础部分，一个是根据玩家的得分计算得到的能力值增益
     * 该函数返回根据玩家的得分计算得到的攻击值增益
     */
    static int attackValGainOfEnemies();

    /** 根据玩家的得分计算得到的防御值增益 */
    static int defendValGainOfEnemies();

    /** 根据玩家的得分计算得到的体力值增益 */
    static int healthPointGainOfEnemies();
};


#endif //ADVENTURE_ATTACK_H
