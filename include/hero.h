#ifndef ADVENTURE_HERO_H
#define ADVENTURE_HERO_H

#include "movable.h"
#include "attack.h"
#include "item.h"

class Hero : public Item, public Aggressive, public Vulnerable, public Movable {
public:
    Hero(int x, int y) ;

    bool move() override ;

    bool beAttacked(Aggressive &attacker) override;
};

#endif //ADVENTURE_HERO_H
