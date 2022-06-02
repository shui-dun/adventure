#ifndef ADVENTURE_BULLET_H
#define ADVENTURE_BULLET_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include "map.h"

class Bullet : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    int direction;

    Bullet(int x, int y, int direction, int attackVal);

    bool move() override;

    bool shouldIMove() override;

    bool beAttacked(Aggressive &attacker) override;
};

#endif //ADVENTURE_BULLET_H
