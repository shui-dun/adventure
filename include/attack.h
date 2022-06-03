#ifndef ADVENTURE_ATTACK_H
#define ADVENTURE_ATTACK_H

#include <curses.h>

class Vulnerable {
public:
    Vulnerable(int healthPoint, int defendVal, chtype injuredSymbol)
            : healthPoint(healthPoint), defendVal(defendVal),
              initHealthPoint(healthPoint), injuredSymbol(injuredSymbol) {}

    virtual ~Vulnerable() = default;

    int healthPoint;

    int initHealthPoint;

    int defendVal;

    chtype injuredSymbol;
};

class Aggressive {
public:
    Aggressive(int attackVal) : attackVal(attackVal) {}

    virtual ~Aggressive() = default;

    int attackVal;

    virtual bool attack(Vulnerable &vulnerable) = 0;
};

class AttackUtils {
public:
    static bool attack(int attackVal, Vulnerable &attacked);
};


#endif //ADVENTURE_ATTACK_H
