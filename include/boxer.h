#ifndef ADVENTURE_BOXER_H
#define ADVENTURE_BOXER_H

#include "move.h"
#include "attack.h"
#include "item.h"

class Boxer : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Boxer(int xPos, int yPos, chtype symbol, int healthPoint, int defendVal,
          int attackVal, unsigned int timeUnits, unsigned int curTimeUnit,
          chtype injuredSymbol, CampEnum camp) :
            Item(xPos, yPos, symbol, camp),
            Vulnerable(healthPoint, defendVal, injuredSymbol),
            Aggressive(attackVal),
            Movable(timeUnits, curTimeUnit) {}
};


class RandomWalkBoxer : public Boxer {
public:
    RandomWalkBoxer(int xPos, int yPos);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;


};

class SmartBoxer : public Boxer {
public:
    SmartBoxer(int xPos, int yPos);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;

};

#endif //ADVENTURE_BOXER_H
