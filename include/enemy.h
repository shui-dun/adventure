#ifndef ADVENTURE_ENEMY_H
#define ADVENTURE_ENEMY_H

#include "move.h"
#include "attack.h"
#include "item.h"

class Enemy : public Item, public Movable, public Vulnerable, public Aggressive {
};


class RandomWalkEnemy : public Enemy {
public:
    RandomWalkEnemy(int x, int y);

    bool move() override;

    bool beAttacked(Aggressive &attacker) override;

    bool shouldIMove() override;

};

class AStarEnemy : public Enemy {
public:
    AStarEnemy(int x, int y);

    bool move() override;

    bool beAttacked(Aggressive &attacker) override;

    bool shouldIMove() override;

};

#endif //ADVENTURE_ENEMY_H
