#ifndef ADVENTURE_BARRIER_H
#define ADVENTURE_BARRIER_H

#include "item.h"
#include "attack.h"
#include "barrier.h"

class Barrier : public Item {
};

class SolidBarrier : public Barrier {
public:

    SolidBarrier(int x, int y);
};

class WeakBarrier : public Barrier, public Vulnerable {
public:

    WeakBarrier(int x, int y);

    bool beAttacked(Aggressive &attacker) override;
};


#endif //ADVENTURE_BARRIER_H
