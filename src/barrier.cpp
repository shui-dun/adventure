#include "barrier.h"
#include "bullet.h"
#include "mixin.h"

SolidBarrier::SolidBarrier(int xPos, int yPos)
        : Barrier(xPos, yPos, ' ', COLOR_PAIR(MapUtils::SOLID_BARRIER), OBJECT) {}

WeakBarrier::WeakBarrier(int xPos, int yPos)
        : Barrier(xPos, yPos, ' ', COLOR_PAIR(MapUtils::WEAK_BARRIER), OBJECT),
          Vulnerable(15, 5) {}
