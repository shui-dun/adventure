#ifndef ADVENTURE_ATTACK_H
#define ADVENTURE_ATTACK_H

#include <curses.h>

class Aggressive {
public:
    Aggressive(int attackVal) : attackVal(attackVal) {}

    virtual ~Aggressive() = default;

    int attackVal;
};

class Vulnerable {
public:
    Vulnerable(int healthPoint, int defendVal, chtype injuredSymbol)
            : healthPoint(healthPoint), defendVal(defendVal),
              initHealthPoint(healthPoint), injuredSymbol(injuredSymbol) {}

    virtual ~Vulnerable() = default;

    // 返回被攻击后是否生还
    virtual bool beAttacked(Aggressive &attacker) = 0;

    int healthPoint;

    int initHealthPoint;

    int defendVal;

    chtype injuredSymbol;
};

class AttackUtils {
public:
    static bool attack(Aggressive &attacker, Vulnerable &attacked);
};


#endif //ADVENTURE_ATTACK_H
