#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include <utility>
#include "item.hpp"
using namespace std;

class Movable {
public:
    int timeInterval; // 两次移动间的时间间隔(ms)

    virtual void move() = 0;
};

#endif