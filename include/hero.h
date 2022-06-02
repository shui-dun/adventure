#ifndef ADVENTURE_HERO_H
#define ADVENTURE_HERO_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include <map>

class Hero : public Item, public Vulnerable, public Movable {
private:
    void updateSymbol();

    static map<chtype, int> directMap;
public:
    chtype inputChar;

    int score;

    int bulletAttackVal;

    int direction;

    Hero(int x, int y);

    bool move() override;

    bool beAttacked(Aggressive &attacker) override;

    bool shouldIMove() override;
};

#endif //ADVENTURE_HERO_H
