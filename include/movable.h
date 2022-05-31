#ifndef ADVENTURE_MOVABLE_H
#define ADVENTURE_MOVABLE_H

class Movable {
public:
    virtual ~Movable() = default;

    int timeInterval; // 两次移动间的时间间隔(ms)

    virtual bool move() = 0;
};

#endif //ADVENTURE_MOVABLE_H
