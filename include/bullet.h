#ifndef ADVENTURE_BULLET_H
#define ADVENTURE_BULLET_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include "map.h"
#include "shooter.h"

class Bullet : public Item, public Movable, public Vulnerable, public Aggressive {
public:
    Bullet(int xPos, int yPos, chtype symbol, CampEnum camp, unsigned int timeUnits, unsigned int curTimeUnit,
           int healthPoint, int defendVal, chtype injuredSymbol, int attackVal, int direction)
            : Item(xPos, yPos, symbol, camp),
              Movable(timeUnits, curTimeUnit),
              Vulnerable(healthPoint, defendVal, injuredSymbol),
              Aggressive(attackVal),
              direction(direction) {}

    int direction;
};


class NormalBullet : public Bullet {
public:
    NormalBullet(int xPos, int yPos, int direction, int attackVal, CampEnum camp);

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;

};

class HeroBullet : public Bullet {
public:
    HeroBullet(int xPos, int yPos, int direction, int attackVal, CampEnum camp, HeroShooter &launcher);

    HeroShooter &launcher;

    bool act() override;

    bool attack(Vulnerable &vulnerable) override;
};

class BulletUtils {
public:
    static bool defaultAction(Bullet &bullet);
};

#endif //ADVENTURE_BULLET_H
