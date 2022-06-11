#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H

#include "archer.h"
#include "item.h"

/**
 * 药水
 */
class Potion : public Item {
public:
    Potion(int xPos, int yPos, const char *symbol, chtype color, CampEnum camp, int value)
            : Item(xPos, yPos, symbol, color,
                   camp), value(value) {}

    int value;

    virtual void actOn(HeroArcher &hero) = 0;
};

/**
 * 治愈药水，恢复玩家体力
 */
class CurePotion : public Potion {
public:
    CurePotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

/**
 * 力量药水，增加玩家攻击力
 */
class StrengthenPotion : public Potion {
public:
    StrengthenPotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

/**
 * 防御药水，增加玩家防御力
 */
class DefendPotion : public Potion {
public:
    DefendPotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

/**
 * 精神控制药水，用于玩家精神控制敌人
 */
class MindControlPotion : public Potion {
public:
    MindControlPotion(int xPos, int yPos);

    void actOn(HeroArcher &hero) override;
};

#endif //ADVENTURE_POTION_H
