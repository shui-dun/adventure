#ifndef ADVENTURE_BARRIER_H
#define ADVENTURE_BARRIER_H

#include "item.h"
#include "attack.h"
#include "barrier.h"

class Barrier : public Item {
public:
    Barrier(int xPos, int yPos, chtype symbol) : Item(xPos, yPos, symbol) {}
};

class SolidBarrier : public Barrier {
public:

    SolidBarrier(int xPos, int yPos);
};

class WeakBarrier : public Barrier, public Vulnerable {
public:

    WeakBarrier(int xPos, int yPos);

    bool beAttacked(Aggressive &attacker) override;
};


#endif //ADVENTURE_BARRIER_H
