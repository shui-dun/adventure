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

    Shooter(int xPos, int yPos, chtype symbol, chtype color, int healthPoint, int defendVal,
            unsigned int timeUnits, unsigned int curTimeUnit,
            CampEnum camp,
            int bulletAttackVal, int direction) :
            Item(xPos, yPos, symbol, color, camp),
            Vulnerable(healthPoint, defendVal),
            Movable(timeUnits, curTimeUnit),
            bulletAttackVal(bulletAttackVal), direction(direction) {}
};


class HeroShooter : public Shooter {
private:
    void updateSymbol();

    static map<chtype, int> directMap;

    Item *findNearestEnemy();

    void mindControl();

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
