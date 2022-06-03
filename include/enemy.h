#ifndef ADVENTURE_ENEMY_H
#define ADVENTURE_ENEMY_H

#include "move.h"
#include "attack.h"
#include "item.h"

class Enemy : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Enemy(int xPos, int yPos, chtype symbol, int healthPoint, int defendVal,
          int attackVal, unsigned int timeUnits, unsigned int curTimeUnit, chtype injuredSymbol) :
            Item(xPos, yPos, symbol),
            Vulnerable(healthPoint, defendVal, injuredSymbol),
            Aggressive(attackVal),
            Movable(timeUnits, curTimeUnit) {}
};


class RandomWalkEnemy : public Enemy {
public:
    RandomWalkEnemy(int xPos, int yPos);

    bool move() override;

    bool beAttacked(Aggressive &attacker) override;

    bool shouldIMove() override;

};

class AStarEnemy : public Enemy {
public:
    AStarEnemy(int xPos, int yPos);

    bool move() override;

    bool beAttacked(Aggressive &attacker) override;

    bool shouldIMove() override;

};

#endif //ADVENTURE_ENEMY_H
