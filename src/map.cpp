#include "map.h"
#include "cursesw.h"
#include "mixin.h"
#include "barrier.h"
#include "boxer.h"
#include "potion.h"
#include <thread>

using namespace std;


#ifdef USE_UNICODE_CHARACTER
const char *MapUtils::EMPTY_SYMBOL = "  ";
const char *MapUtils::BARRIER_SYMBOL = "  ";
const char *MapUtils::BOXER_SYMBOL = "🙃";
const char *MapUtils::BULLET_SYMBOL = "〇";
const char *MapUtils::CURE_POTION_SYMBOL = "💗";
const char *MapUtils::STRENGTH_POTION_SYMBOL = "🏹";
const char *MapUtils::DEFEND_POTION_SYMBOL = "🔰";
const char *MapUtils::MIND_CONTROL_POTION_SYMBOL = "🌀";
const char *MapUtils::ENEMY_SHOOTER_SYMBOL = "🤡";
const char *MapUtils::HERO_SHOOTER_UP_SYMBOL = "▲▲";
const char *MapUtils::HERO_SHOOTER_DOWN_SYMBOL = "▼▼";
const char *MapUtils::HERO_SHOOTER_LEFT_SYMBOL = "⮜⬤";
const char *MapUtils::HERO_SHOOTER_RIGHT_SYMBOL = "⬤➤";
#else
const char *MapUtils::EMPTY_SYMBOL = " ";
const char *MapUtils::BARRIER_SYMBOL = " ";
const char *MapUtils::BOXER_SYMBOL = "O";
const char *MapUtils::BULLET_SYMBOL = "*";
const char *MapUtils::CURE_POTION_SYMBOL = "+";
const char *MapUtils::STRENGTH_POTION_SYMBOL = "!";
const char *MapUtils::DEFEND_POTION_SYMBOL = "U";
const char *MapUtils::MIND_CONTROL_POTION_SYMBOL = "@";
const char *MapUtils::ENEMY_SHOOTER_SYMBOL = "X";
const char *MapUtils::HERO_SHOOTER_UP_SYMBOL = "A";
const char *MapUtils::HERO_SHOOTER_DOWN_SYMBOL = "V";
const char *MapUtils::HERO_SHOOTER_LEFT_SYMBOL = "<";
const char *MapUtils::HERO_SHOOTER_RIGHT_SYMBOL = ">";
#endif

int MapUtils::lines = 0;

int MapUtils::cols = 0;

void MapUtils::init() {
    setlocale(LC_ALL, "");
    initscr();
    lines = LINES < 26 ? LINES : 26;
    cols = COLS < 52 ? COLS : 52;
    raw();
    noecho();
    curs_set(0);
    initColor();
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
    myHero = new HeroShooter(cols - 2, lines - 2);
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
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < lines; ++j) {
            updateAxis(i, j, globalMap[i][j]);
        }
    }
    refresh();
}

void MapUtils::updateAxis(int x, int y, Item *item) {
#ifdef USE_UNICODE_CHARACTER
    int drawX = 2 * x;
#else
    int drawX = x;
#endif
    globalMap[x][y] = item;
    if (item) {
        attron(item->color);
        mvprintw(y, drawX, item->symbol);
        attroff(item->color);
    } else {
        attron(COLOR_PAIR(BACKGROUND));
        mvprintw(y, drawX, EMPTY_SYMBOL);
        attroff(COLOR_PAIR(BACKGROUND));
    }
}

void MapUtils::createCharacters() {
    mapMutex.lock();
    for (int i = 0; i < 20; ++i) {
        createRandomCharacter();
    }
    refresh();
    mapMutex.unlock();
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(6000));
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
        mvprintw(0, 2, "HP: %d ATK: %d DEF: %d MindCtrl: %d SCORE: %d            ",
                 myHero->healthPoint, myHero->bulletAttackVal, myHero->defendVal, myHero->nMindControl, myHero->score);
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
    if (randVal < 0.4) {
        item = new RandomWalkBoxer(xPos, yPos);
    } else if (randVal < 0.8) {
        item = new RandomWalkShooter(xPos, yPos);
    } else if (randVal < 0.85) {
        item = new MindControlPotion(xPos, yPos);
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
    attron(COLOR_PAIR(GAME_OVER_INFO));
    for (int i = 0; i < strs.size(); ++i) {
#ifdef USE_UNICODE_CHARACTER
        mvprintw(lines / 2 - 3 + i, cols - 25, strs[i]);
#else
        mvprintw(lines / 2 - 3 + i, cols / 2 - 25, strs[i]);
#endif
    }
    attroff(COLOR_PAIR(GAME_OVER_INFO));
    mvprintw(lines, 2, "Press Big Q to Continue...                       ");
    refresh();
    while (getch() != 'Q') {
    }
    endwin();
}

void MapUtils::pause() {
    mvprintw(lines, 2,
             "Game Paused, Press p to Continue                               ");
    refresh();
    while (getch() != 'p') {
    }
    mvprintw(lines, 1,
             "                                                               ");
    refresh();
}

bool MapUtils::isAxisLegal(int xPos, int yPos) {
    return xPos >= 0 && xPos < cols && yPos >= 0 && yPos < lines;
}

void MapUtils::initColor() {
    start_color();
    init_pair(BACKGROUND, COLOR_WHITE, COLOR_WHITE);
    init_pair(GAME_OVER_INFO, COLOR_BLACK, COLOR_WHITE);
    init_pair(SOLID_BARRIER, COLOR_BLACK, COLOR_BLACK);
    init_pair(WEAK_BARRIER, COLOR_CYAN, COLOR_CYAN);
    init_pair(ENEMY, COLOR_BLUE, COLOR_WHITE);
    init_pair(MIND_CONTROL, COLOR_WHITE, COLOR_BLUE);
    init_pair(HERO, COLOR_RED, COLOR_WHITE);
    init_pair(POTION, COLOR_WHITE, COLOR_GREEN);
}

void MapUtils::showInfoOfItem(Vulnerable &vulnerable) {
    auto aggressive = dynamic_cast<Aggressive *>(&vulnerable);
    mvprintw(lines - 1, 2,
             "Attack: Enemy(ATK=%d,DEF=%d,HP=%d)                ",
             aggressive == nullptr ? 0 : aggressive->attackVal,
             vulnerable.defendVal, vulnerable.healthPoint);
}
