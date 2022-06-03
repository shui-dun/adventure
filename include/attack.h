#ifndef ADVENTURE_ATTACK_H
#define ADVENTURE_ATTACK_H

#include <curses.h>

class Vulnerable {
public:
    Vulnerable(int healthPoint, int defendVal)
            : healthPoint(healthPoint), defendVal(defendVal),
              initHealthPoint(healthPoint) {}

    virtual ~Vulnerable() = default;

    int healthPoint;

    int initHealthPoint;

    int defendVal;
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

    static bool attack(Aggressive &attacker, Vulnerable &attacked);

    static int attackValGainOfEnemies();

    static int defendValGainOfEnemies();

    static int healthPointGainOfEnemies();
};


#endif //ADVENTURE_ATTACK_H
