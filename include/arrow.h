#ifndef ADVENTURE_ARROW_H
#define ADVENTURE_ARROW_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include "map.h"
#include "archer.h"

class Arrow : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Arrow(int xPos, int yPos, const char *symbol, chtype color, CampEnum camp, unsigned int timeUnits,
          unsigned int curTimeUnit,
          int healthPoint, int defendVal, int attackVal, int direction)
            : Item(xPos, yPos, symbol, color, camp),
              Movable(timeUnits, curTimeUnit),
              Vulnerable(healthPoint, defendVal),
              Aggressive(attackVal),
              direction(direction) {}

    int direction;
};


class NormalArrow : public Arrow {
public:
    NormalArrow(int xPos, int yPos, Archer &launcher);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;

};

class HeroArrow : public Arrow {
public:
    HeroArrow(int xPos, int yPos, HeroArcher &launcher);

    HeroArcher &launcher;

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;
};

class ArrowUtils {
public:
    static bool defaultAction(Arrow &bullet);
};

#endif //ADVENTURE_ARROW_H
