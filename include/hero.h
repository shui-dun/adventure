#ifndef ADVENTURE_HERO_H
#define ADVENTURE_HERO_H

#include "move.h"
#include "attack.h"
#include "item.h"

class Hero : public Item, public Vulnerable, public Movable {
private:
    void updateSymbol();
public:
    int score;

    int bulletAttackVal = 2;

    int direction;

    Hero(int x, int y) ;

    bool move() override ;

    bool beAttacked(Aggressive &attacker) override;
};

#endif //ADVENTURE_HERO_H
