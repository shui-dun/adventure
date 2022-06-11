#ifndef ADVENTURE_ITEM_H
#define ADVENTURE_ITEM_H

#include <cursesw.h>

/**
 * 物品
 */
class Item {
public:

    /** 阵营的枚举类 */
    enum CampEnum {
        OBJECT,
        ENEMY,
        PLAYER
    };

    Item(int xPos, int yPos, const char *symbol, chtype color, CampEnum camp)
            : xPos(xPos), yPos(yPos), symbol(symbol), color(color), camp(camp) {}

    virtual ~Item() = default;

    /** 该物品所属的阵营 */
    CampEnum camp;

    /** x坐标 */
    int xPos;

    /** y坐标 */
    int yPos;

    /** 绘制的符号 */
    const char *symbol;

    /** 绘制的符号的颜色 */
    chtype color;

};

#endif //ADVENTURE_ITEM_H
