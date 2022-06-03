#ifndef ADVENTURE_ITEM_H
#define ADVENTURE_ITEM_H

#include <curses.h>

class Item {
public:

    enum CampEnum {
        OBJECT,
        ENEMY,
        PLAYER,
        PLAYER2
    };

    Item(int xPos, int yPos, chtype symbol, chtype color, CampEnum camp)
            : xPos(xPos), yPos(yPos), symbol(symbol), color(color), camp(camp) {}

    virtual ~Item() = default;

    CampEnum camp;

    int xPos;
    int yPos;
    chtype symbol;
    chtype color;

};

#endif //ADVENTURE_ITEM_H
