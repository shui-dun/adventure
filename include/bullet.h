#ifndef ADVENTURE_BULLET_H
#define ADVENTURE_BULLET_H

#include "movable.h"
#include "attack.h"
#include "item.h"

class Bullet : public Item, public Movable, public Vulnerable, public Aggressive {
    int direction;
public:
    Bullet(int x, int y, int direction);

    bool move() override ;

    bool beAttacked(Aggressive &attacker) override;
};

#endif //ADVENTURE_BULLET_H
