#ifndef ADVENTURE_MOVE_H
#define ADVENTURE_MOVE_H

class Movable {
public:
    Movable(unsigned int timeUnits, unsigned int curTimeUnit)
            : timeUnits(timeUnits), curTimeUnit(curTimeUnit) {}

    virtual ~Movable() = default;

    /** 两次移动间的时间间隔，每timeUnits个时间单位移动一次 */
    unsigned int timeUnits;

    /** 辅助timeUnits进行角色是否应该移动的判断
     * 在每个时间单位，curTimeUnit=(curTimeUnit+1)%timeUnits
     * 当curTimeUnit为0时角色应该运动
     */
    unsigned int curTimeUnit;

    virtual bool act() = 0;
};

class MoveUtils {
public:
    /** 判断一个角色是否应该移动 */
    static bool shouldMove(Movable &movable);
};


#endif //ADVENTURE_MOVE_H
