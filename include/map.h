#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"
#include "bullet.h"

class MapUtils {
    static void createRandomCharacter();

public:


    static const char *EMPTY_SYMBOL;
    static const char *BARRIER_SYMBOL;
    static const char *BOXER_SYMBOL;
    static const char *BULLET_SYMBOL;
    static const char *CURE_POTION_SYMBOL;
    static const char *STRENGTH_POTION_SYMBOL;
    static const char *DEFEND_POTION_SYMBOL;
    static const char *MIND_CONTROL_POTION_SYMBOL;
    static const char *ENEMY_SHOOTER_SYMBOL;
    static const char *HERO_SHOOTER_UP_SYMBOL;
    static const char *HERO_SHOOTER_DOWN_SYMBOL;
    static const char *HERO_SHOOTER_LEFT_SYMBOL;
    static const char *HERO_SHOOTER_RIGHT_SYMBOL;


    enum colorEnum {
        BACKGROUND = 1,
        GAME_OVER_INFO,
        SOLID_BARRIER,
        WEAK_BARRIER,
        ENEMY,
        MIND_CONTROL,
        HERO,
        POTION
    };

    static int lines;

    static int cols;

    static void init();

    static void initColor();

    static void genWall();

    static void genRandomMap();

    static void drawInit();

    static void updateAxis(int x, int y, Item *item);

    static void createCharacters();

    static void showInfo();

    static void pause();

    static void showGameOver();

    static bool isAxisLegal(int xPos, int yPos);

    static void showInfoOfItem(Vulnerable &vulnerable);
};


#endif //ADVENTURE_MAP_H
