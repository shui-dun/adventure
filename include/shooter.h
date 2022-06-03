#ifndef ADVENTURE_SHOOTER_H
#define ADVENTURE_SHOOTER_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include <map>


class Shooter : public Item, public Vulnerable, public Movable {
public:

    int bulletAttackVal;

    int direction;

    Shooter(int xPos, int yPos, chtype symbol, int healthPoint, int defendVal,
            unsigned int timeUnits, unsigned int curTimeUnit,
            chtype injuredSymbol, CampEnum camp,
            int bulletAttackVal, int direction) :
            Item(xPos, yPos, symbol, camp),
            Vulnerable(healthPoint, defendVal, injuredSymbol),
            Movable(timeUnits, curTimeUnit),
            bulletAttackVal(bulletAttackVal), direction(direction) {}
};


class HeroShooter : public Shooter {
private:
    void updateSymbol();

    static map<chtype, int> directMap;

public:
    chtype inputChar;

    int score;

    HeroShooter(int xPos, int yPos);

    bool act() override;
};

class RandomWalkShooter : public Shooter {
public:
    RandomWalkShooter(int xPos, int yPos);

    bool act() override;
};

class SmartShooter : public Shooter {

};

class ShooterUtils {

};

#endif //ADVENTURE_SHOOTER_H
