#ifndef ITEM_HPP
#define ITEM_HPP

class Item {
    // 告诉编译器这是一个抽象类，不然不能用dynamic_cast
    virtual void foo() {}

protected:
    int xPos;
    int yPos;
    char symbol;
};

#endif