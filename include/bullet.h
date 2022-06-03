#ifndef ADVENTURE_BULLET_H
#define ADVENTURE_BULLET_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include "map.h"
#include "shooter.h"

class Bullet : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Shooter &launcher;

    int direction;

    Bullet(int xPos, int yPos, int direction, int attackVal, Shooter &launcher, CampEnum camp);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;
};

#endif //ADVENTURE_BULLET_H
