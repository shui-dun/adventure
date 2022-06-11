#ifndef ADVENTURE_BARRIER_H
#define ADVENTURE_BARRIER_H

#include "item.h"
#include "attack.h"
#include "barrier.h"

/**
 * 围墙
 */
class Barrier : public Item {
public:
    Barrier(int xPos, int yPos, const char *symbol, chtype color, CampEnum camp)
            : Item(xPos, yPos, symbol, color, camp) {}
};

/**
 * 坚固的围墙
 */
class SolidBarrier : public Barrier {
public:

    SolidBarrier(int xPos, int yPos);
};

/**
 * 可以受到伤害的围墙
 */
class WeakBarrier : public Barrier, public Vulnerable {
public:

    WeakBarrier(int xPos, int yPos);

};


#endif //ADVENTURE_BARRIER_H
