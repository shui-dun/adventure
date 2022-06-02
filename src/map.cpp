#include "map.h"
#include "curses.h"
#include "mixin.h"
#include "barrier.h"
#include "enemy.h"
#include "potion.h"
#include <thread>

using namespace std;

void MapUtils::init() {
    initscr();
    raw();
    noecho();
    curs_set(0);
    start_color();
    init_pair(BACKGROUND, COLOR_WHITE, COLOR_WHITE);
    init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
    init_pair(SOLID_BARRIER, COLOR_BLACK, COLOR_BLACK);
    init_pair(WEAK_BARRIER_INIT, COLOR_BLUE, COLOR_BLUE);
    init_pair(WEAK_BARRIER_INJURED, COLOR_RED, COLOR_RED);
    init_pair(NORMAL_INIT, COLOR_BLUE, COLOR_WHITE);
    init_pair(NORMAL_INJURED, COLOR_RED, COLOR_WHITE);
    init_pair(ME, COLOR_CYAN, COLOR_WHITE);
    init_pair(CURE_POTION, COLOR_WHITE, COLOR_GREEN);
    init_pair(STRENGTHEN_POTION, COLOR_WHITE, COLOR_GREEN);
    attron(COLOR_PAIR(INFO));
    genWall();
    genRandomMap();
    drawInit();
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
    myHero = new Hero(COLS - 2, LINES - 2);
    globalMap[COLS - 2][LINES - 2] = myHero;
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

void MapUtils::drawInit() {
    for (int j = 0; j < LINES; ++j) {
        move(j, 0);
        for (int i = 0; i < COLS; ++i) {
            if (globalMap[i][j] == nullptr) {
                addch(' ' | COLOR_PAIR(BACKGROUND));
            } else {
                addch(globalMap[i][j]->symbol);
            }
        }
    }
    refresh();
}

void MapUtils::updateAxis(int x, int y, Item *item) {
    globalMap[x][y] = item;
    if (item) {
        mvaddch(y, x, item->symbol);
    } else {
        mvaddch(y, x, ' ' | COLOR_PAIR(BACKGROUND));
    }
}

void MapUtils::createCharacters() {
    mapMutex.lock();
    for (int i = 0; i < 25; ++i) {
        createRandomCharacter();
    }
    refresh();
    mapMutex.unlock();
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(4000));
        mapMutex.lock();
        createRandomCharacter();
        refresh();
        mapMutex.unlock();
    }
}

void MapUtils::showInfo() {
    while (true) {
        mapMutex.lock();
        mvprintw(0, 1, "HP: %d ATK: %d SCORES: %d", myHero->healthPoint, myHero->bulletAttackVal, myHero->score);
        mapMutex.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void MapUtils::createRandomCharacter() {
    int xPos, yPos;
    uniform_int_distribution<int> xDistribution(1, COLS - 2);
    uniform_int_distribution<int> yDistribution(1, LINES - 2);
    while (true) {
        xPos = xDistribution(randEngine);
        yPos = yDistribution(randEngine);
        if (globalMap[xPos][yPos] == nullptr) {
            break;
        }
    }
    Item *item = nullptr;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    double randVal = distribution(randEngine);
    if (randVal < 0.9) {
        item = new RandomWalkEnemy(xPos, yPos);
    } else if (randVal < 0.95) {
        item = new CurePotion(xPos, yPos);
    } else {
        item = new StrengthenPotion(xPos, yPos);
    }
    updateAxis(xPos, yPos, item);
}
