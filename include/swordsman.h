#ifndef ADVENTURE_SWORDSMAN_H
#define ADVENTURE_SWORDSMAN_H

#include "move.h"
#include "attack.h"
#include "item.h"

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


class RandomWalkSwordsman : public Swordsman {
public:
    RandomWalkSwordsman(int xPos, int yPos);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;


};

class SmartSwordsman : public Swordsman {
public:
    SmartSwordsman(int xPos, int yPos);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;

};

class SwordsmanUtils {
public:
    static bool defaultAction(Swordsman *boxer, int newX, int newY);
};

#endif //ADVENTURE_SWORDSMAN_H
