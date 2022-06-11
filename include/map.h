#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "item.h"
#include "arrow.h"
#include "archer.h"
#include <vector>
#include <utility>
#include <random>
#include <mutex>

using namespace std;

class MapUtils {

    /**
     * 产生一行墙壁
     * @param fromY 起始y坐标
     * @param toY 终止y坐标（包含）
     * @param x x坐标
     * @param horizontal 是否水平，当为false时，产生从(x,fromY)到(x,toY)的一行墙壁;
     *                   当为true时，产生从(fromY,x)到(toY,x)的一行墙壁
     */
    static void genLineOfWall(int fromY, int toY, int x, bool horizontal);

public:

    /** 游戏地图 */
    static vector<vector<Item *>> gameMap;

    /** 玩家 */
    static HeroArcher *myHero;

    /** 游戏是否结束 */
    static bool gameOver;

    /** 访问gameMap的锁 */
    static mutex mapMutex;

    /** 随机数引擎 */
    static mt19937 randEngine;

    /** 初始化地图 */
    static void init();

    /** 产生围墙 */
    static void genWall();

    /** 产生随机的点状地图 */
    static void genRandomMap();

    /** 使用递归分割算法为左上角为(xFrom, yFrom)、右下角为(xTo, yTo)的区域产生随机地图 */
    static void genRecursiveSegmentationMap(int xFrom, int yFrom, int xTo, int yTo);

    /** 创建初始化的角色和物品 */
    static void createInitCharacters();

    /** 判断一个坐标是否合法（没有越界） */
    static bool isAxisLegal(int xPos, int yPos);

    /**
     * 得到一个角色向某个方向运动一格后的新坐标
     * @param item 目标
     * @param direction 目标运行的方向
     * @return 新的坐标pair<x,y>
     */
    static pair<int, int> nextPosOfDirection(Item &item, int direction);

    /** 得到一个坐标向某个方向运动一格后的新坐标 */
    static pair<int, int> nextPosOfDirection(int x, int y, int direction);

    /** 将地图上所有的角色全部运行一次 */
    static void moveAllCharacters();

    /** 玩家的行动 */
    static void moveMyHero();

    /** 将某角色跳转到指定的坐标 */
    static void moveToPos(Item &item, int newX, int newY);

    /** 地图的行数 */
    static int nLines();

    /** 地图的列数 */
    static int nCols();

    /** 随机创建一个角色或物品*/
    static void createRandomCharacter();

    /** 判断一个坐标(destX,destY)位于物品me的什么方向
     * 调用之前请保证指定物品和指定坐标位于同一直线上
     */
    static int locatedAtDirection(Item &me, int destX, int destY);
};


#endif //ADVENTURE_MAP_H
