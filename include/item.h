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

    Item(int xPos, int yPos, chtype symbol, CampEnum camp)
            : xPos(xPos), yPos(yPos), symbol(symbol), camp(camp) {}

    virtual ~Item() = default;

    CampEnum camp;

    int xPos;
    int yPos;
    chtype symbol;

};

#endif //ADVENTURE_ITEM_H
