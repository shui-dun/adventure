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

    /** 绘图的符号列表 */
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

    /** 颜色枚举类 */
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

    /** 初始化屏幕 */
    static void init();

    /** 绘画出整个界面 */
    static void draw();

    /** 暂停 */
    static void pause();

    /** 游戏结束的界面 */
    static void showGameOver();

    /** 绘制指定坐标 */
    static void drawAxis(int x, int y);

    /** 当前敌人的信息 **/
    static string curEnemyInfo;

    /** 更新当前敌人的信息 **/
    static void genCurEnemyInfo(Vulnerable &enemy);
};

#endif //ADVENTURE_DRAW_H
