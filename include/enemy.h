#ifndef ADVENTURE_ENEMY_H
#define ADVENTURE_ENEMY_H

#include "movable.h"
#include "attack.h"
#include "item.h"

class Enemy : public Item, public Movable, public Vulnerable, public Aggressive {
};


class RandomWalkEnemy : public Enemy {
public:
    RandomWalkEnemy(int x, int y) ;

    bool move() override ;

    bool beAttacked(Aggressive &attacker) override ;

};

class AStarEnemy : public Enemy {
public:
    AStarEnemy(int x, int y);

    bool move() override ;

    bool beAttacked(Aggressive &attacker) override;

};

#endif //ADVENTURE_ENEMY_H
