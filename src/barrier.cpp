#include "barrier.h"
#include "arrow.h"
#include "draw.h"

SolidBarrier::SolidBarrier(int xPos, int yPos)
        : Barrier(xPos, yPos, DrawUtils::BARRIER_SYMBOL, COLOR_PAIR(DrawUtils::SOLID_BARRIER), OBJECT) {}

WeakBarrier::WeakBarrier(int xPos, int yPos)
        : Barrier(xPos, yPos, DrawUtils::BARRIER_SYMBOL, COLOR_PAIR(DrawUtils::WEAK_BARRIER), OBJECT),
          Vulnerable(15, 5) {}
