#ifndef ADVENTURE_SHOOTER_H
#define ADVENTURE_SHOOTER_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include <map>

class Shooter : public Item, public Vulnerable, public Movable {
private:
    void updateSymbol();

    static map<chtype, int> directMap;
public:
    chtype inputChar;

    int score;

    int bulletAttackVal;

    int direction;

    Shooter(int xPos, int yPos);

    bool act() override;
};

#endif //ADVENTURE_SHOOTER_H
