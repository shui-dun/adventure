#ifndef ADVENTURE_BULLET_H
#define ADVENTURE_BULLET_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include "map.h"
#include "hero.h"

class Bullet : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Hero &launcher;

    int direction;

    Bullet(int xPos, int yPos, int direction, int attackVal, Hero &launcher);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;
};

#endif //ADVENTURE_BULLET_H
