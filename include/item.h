#ifndef ADVENTURE_ITEM_H
#define ADVENTURE_ITEM_H

#include <curses.h>

class Item {
public:

    Item(int xPos, int yPos, chtype symbol) : xPos(xPos), yPos(yPos), symbol(symbol) {}

    virtual ~Item() = default;

    int xPos{};
    int yPos{};
    chtype symbol{};
};

#endif //ADVENTURE_ITEM_H
