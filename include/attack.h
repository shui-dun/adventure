#ifndef ADVENTURE_ATTACK_H
#define ADVENTURE_ATTACK_H

#include <curses.h>

class Aggressive {
public:
    virtual ~Aggressive() = default;

    int attackVal;
};

class Vulnerable {
public:
    virtual ~Vulnerable() = default;

    // 返回被攻击后是否生还
    virtual bool beAttacked(Aggressive &attacker) = 0;

    int healthPoint;

    int defendVal;
};

class AttackUtils {
public:
    static bool attack(Aggressive &attacker, Vulnerable &attacked, unsigned int ch);
};


#endif //ADVENTURE_ATTACK_H
