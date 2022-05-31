#include "map.h"
#include "curses.h"
#include "mixin.h"
#include "barrier.h"

using namespace std;

void MapUtils::init() {
    initscr();
    raw();
    noecho();
    curs_set(0);
    start_color();
    init_pair(BACKGROUND, COLOR_WHITE, COLOR_WHITE);
    init_pair(SOLID_BARRIER, COLOR_BLACK, COLOR_BLACK);
    init_pair(WEAK_BARRIER_INIT, COLOR_BLUE, COLOR_BLUE);
    init_pair(WEAK_BARRIER_INJURED, COLOR_RED, COLOR_RED);
    init_pair(NORMAL_INIT, COLOR_BLUE, COLOR_WHITE);
    init_pair(NORMAL_INJURED, COLOR_RED, COLOR_WHITE);
    init_pair(ME, COLOR_CYAN, COLOR_WHITE);
    init_pair(CURE_POTION, COLOR_WHITE, COLOR_GREEN);
    init_pair(STRENGTHEN_POTION, COLOR_WHITE, COLOR_YELLOW);
    wbkgd(stdscr, COLOR_PAIR(BACKGROUND));
    genWall();
    genRandomMap();
    draw();
}

void MapUtils::genWall() {
    globalMap.assign(COLS, vector<Item *>(LINES, nullptr));
    for (int i = 0; i < LINES; ++i) {
        globalMap[0][i] = new SolidBarrier(0, i);
        globalMap[COLS - 1][i] = new SolidBarrier(COLS - 1, i);
    }
    for (int i = 1; i < COLS - 1; ++i) {
        globalMap[i][0] = new SolidBarrier(i, 0);
        globalMap[i][LINES - 1] = new SolidBarrier(i, LINES - 1);
    }
}

void MapUtils::genRandomMap() {
// 除了这种点状地图，以后还要产生几种迷宫地图
    for (int i = 1; i < COLS - 1; ++i) {
        for (int j = 1; j < LINES - 1; ++j) {
            if (globalMap[i][j] != nullptr) {
                continue;
            }
            uniform_real_distribution<float> distribution(0.0, 1.0);
            double randVal = distribution(randEngine);
            if (randVal < 0.8) {
                continue;
            } else if (randVal < 0.9) {
                globalMap[i][j] = new SolidBarrier(i, j);
            } else {
                globalMap[i][j] = new WeakBarrier(i, j);
            }
        }
    }
}

void MapUtils::draw() {
    for (auto &v: globalMap) {
        for (auto item: v) {
            if (item != nullptr) {
                mvaddch(item->yPos, item->xPos, item->symbol);
            }
        }
    }
    refresh();
}

void MapUtils::updateAxis(int x, int y, Item *item) {
    globalMap[x][y] = item;
    mvaddch(y, x, item->symbol);
}
