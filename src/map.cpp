#include "map.h"
#include "curses.h"
#include "mixin.h"
#include "barrier.h"
#include "enemy.h"
#include "potion.h"
#include <thread>

using namespace std;

int MapUtils::lines = 0;

int MapUtils::cols = 0;

void MapUtils::init() {
    initscr();
    lines = LINES < 26 ? LINES : 26;
    cols = COLS < 52 ? COLS : 52;
    raw();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(0);
    start_color();
    init_pair(BACKGROUND, COLOR_WHITE, COLOR_WHITE);
    init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
    init_pair(INFO2, COLOR_BLACK, COLOR_WHITE);
    init_pair(SOLID_BARRIER, COLOR_BLACK, COLOR_BLACK);
    init_pair(WEAK_BARRIER_INIT, COLOR_BLUE, COLOR_BLUE);
    init_pair(WEAK_BARRIER_INJURED, COLOR_RED, COLOR_RED);
    init_pair(NORMAL_INIT, COLOR_BLUE, COLOR_WHITE);
    init_pair(NORMAL_INJURED, COLOR_RED, COLOR_WHITE);
    init_pair(ME, COLOR_CYAN, COLOR_WHITE);
    init_pair(POTION, COLOR_WHITE, COLOR_GREEN);
    attron(COLOR_PAIR(INFO));
    genWall();
    genRandomMap();
    drawInit();
}

void MapUtils::genWall() {
    globalMap.assign(cols, vector<Item *>(lines, nullptr));
    for (int i = 0; i < lines; ++i) {
        globalMap[0][i] = new SolidBarrier(0, i);
        globalMap[cols - 1][i] = new SolidBarrier(cols - 1, i);
    }
    for (int i = 1; i < cols - 1; ++i) {
        globalMap[i][0] = new SolidBarrier(i, 0);
        globalMap[i][lines - 1] = new SolidBarrier(i, lines - 1);
    }
    myHero = new Hero(cols - 2, lines - 2);
    globalMap[cols - 2][lines - 2] = myHero;
}

void MapUtils::genRandomMap() {
// 除了这种点状地图，以后还要产生几种迷宫地图
    for (int i = 1; i < cols - 1; ++i) {
        for (int j = 1; j < lines - 1; ++j) {
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
    for (int j = 0; j < lines; ++j) {
        move(j, 0);
        for (int i = 0; i < cols; ++i) {
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
        if (gameOver) {
            mapMutex.unlock();
            return;
        }
        createRandomCharacter();
        refresh();
        mapMutex.unlock();
    }
}

void MapUtils::showInfo() {
    while (true) {
        mapMutex.lock();
        if (gameOver) {
            mapMutex.unlock();
            return;
        }
        mvprintw(0, 1, "HP: %d ATK: %d DEF: %d SCORES: %d            ",
                 myHero->healthPoint, myHero->bulletAttackVal, myHero->defendVal, myHero->score);
        mapMutex.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void MapUtils::createRandomCharacter() {
    int xPos, yPos;
    uniform_int_distribution<int> xDistribution(1, cols - 2);
    uniform_int_distribution<int> yDistribution(1, lines - 2);
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
    if (randVal < 0.85) {
        item = new RandomWalkEnemy(xPos, yPos);
    } else if (randVal < 0.9) {
        item = new CurePotion(xPos, yPos);
    } else if (randVal < 0.95) {
        item = new StrengthenPotion(xPos, yPos);
    } else {
        item = new DefendPotion(xPos, yPos);
    }
    updateAxis(xPos, yPos, item);
}

void MapUtils::showGameOver() {
    vector<const char *> strs = {"  __ _  __ _ _ __ ___   ___    _____   _____ _ __",
                                 " / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|",
                                 "| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |",
                                 " \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|",
                                 " |___/"};
    attron(COLOR_PAIR(INFO2));
    for (int i = 0; i < strs.size(); ++i) {
        mvprintw(lines / 2 - 3 + i, cols / 2 - 25, strs[i]);
    }
    attron(COLOR_PAIR(INFO));
    mvprintw(lines - 1, 1, "Press Big Q to Continue...");
    refresh();
    while (getch() != 'Q') {
    }
    endwin();
}
