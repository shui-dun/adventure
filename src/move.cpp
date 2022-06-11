#include "move.h"

bool MoveUtils::shouldMove(Movable &movable) {
    movable.curTimeUnit = (movable.curTimeUnit + 1) % movable.timeUnits;
    return movable.curTimeUnit == 0;
}