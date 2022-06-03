#include "barrier.h"
#include "bullet.h"
#include "mixin.h"

SolidBarrier::SolidBarrier(int xPos, int yPos)
        : Barrier(xPos, yPos, ' ' | COLOR_PAIR(SOLID_BARRIER), OBJECT) {}

WeakBarrier::WeakBarrier(int xPos, int yPos)
        : Barrier(xPos, yPos, ' ' | COLOR_PAIR(WEAK_BARRIER_INIT), OBJECT),
          Vulnerable(15, 5, ' ' | COLOR_PAIR(WEAK_BARRIER_INJURED)) {}
