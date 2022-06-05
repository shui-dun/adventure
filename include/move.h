#ifndef ADVENTURE_MOVE_H
#define ADVENTURE_MOVE_H

class Movable {
public:
    Movable(unsigned int timeUnits, unsigned int curTimeUnit) : timeUnits(timeUnits), curTimeUnit(curTimeUnit) {}

    virtual ~Movable() = default;

    unsigned int timeUnits; // 两次移动间的时间间隔

    unsigned int curTimeUnit;

    virtual bool act() = 0;
};


#endif //ADVENTURE_MOVE_H
