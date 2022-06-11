#ifndef ADVENTURE_DRAW_H
#define ADVENTURE_DRAW_H

#include <utility>
#include <string>
#include "item.h"
#include "move.h"
#include "attack.h"
using namespace std;

class DrawUtils {
public:
    static const char *EMPTY_SYMBOL;
    static const char *BARRIER_SYMBOL;
    static const char *SWORDSMAN_SYMBOL;
    static const char *ARROW_SYMBOL;
    static const char *CURE_POTION_SYMBOL;
    static const char *STRENGTH_POTION_SYMBOL;
    static const char *DEFEND_POTION_SYMBOL;
    static const char *MIND_CONTROL_POTION_SYMBOL;
    static const char *ENEMY_ARCHER_SYMBOL;
    static const char *HERO_ARCHER_UP_SYMBOL;
    static const char *HERO_ARCHER_DOWN_SYMBOL;
    static const char *HERO_ARCHER_LEFT_SYMBOL;
    static const char *HERO_ARCHER_RIGHT_SYMBOL;


    enum colorEnum {
        BACKGROUND = 1,
        GAME_OVER_INFO,
        SOLID_BARRIER,
        WEAK_BARRIER,
        RANDOM_WALK_ENEMY,
        SMART_ENEMY,
        MIND_CONTROL,
        HERO,
        POTION
    };

    static void init();

    static void draw();

    static void pause();

    static void showGameOver();

    static void updateAxis(int x, int y);

    static string curEnemyInfo;

    static void genCurEnemyInfo(Vulnerable &enemy);
};

#endif //ADVENTURE_DRAW_H
