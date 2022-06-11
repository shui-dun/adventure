#include "draw.h"
#include "map.h"
#include "barrier.h"
#include <curses.h>
#include <thread>

#ifdef USE_UNICODE_CHARACTER
const char *DrawUtils::EMPTY_SYMBOL = "  ";
const char *DrawUtils::BARRIER_SYMBOL = "  ";
const char *DrawUtils::SWORDSMAN_SYMBOL = "🙃";
const char *DrawUtils::ARROW_SYMBOL = "〇";
const char *DrawUtils::CURE_POTION_SYMBOL = "💗";
const char *DrawUtils::STRENGTH_POTION_SYMBOL = "🏹";
const char *DrawUtils::DEFEND_POTION_SYMBOL = "🔰";
const char *DrawUtils::MIND_CONTROL_POTION_SYMBOL = "🌀";
const char *DrawUtils::ENEMY_ARCHER_SYMBOL = "🤡";
const char *DrawUtils::HERO_ARCHER_UP_SYMBOL = "▲▲";
const char *DrawUtils::HERO_ARCHER_DOWN_SYMBOL = "▼▼";
const char *DrawUtils::HERO_ARCHER_LEFT_SYMBOL = "⮜⬤";
const char *DrawUtils::HERO_ARCHER_RIGHT_SYMBOL = "⬤➤";
#else
const char *DrawUtils::EMPTY_SYMBOL = " ";
const char *DrawUtils::BARRIER_SYMBOL = " ";
const char *DrawUtils::SWORDSMAN_SYMBOL = "O";
const char *DrawUtils::ARROW_SYMBOL = "*";
const char *DrawUtils::CURE_POTION_SYMBOL = "+";
const char *DrawUtils::STRENGTH_POTION_SYMBOL = "!";
const char *DrawUtils::DEFEND_POTION_SYMBOL = "U";
const char *DrawUtils::MIND_CONTROL_POTION_SYMBOL = "@";
const char *DrawUtils::ENEMY_ARCHER_SYMBOL = "X";
const char *DrawUtils::HERO_ARCHER_UP_SYMBOL = "A";
const char *DrawUtils::HERO_ARCHER_DOWN_SYMBOL = "V";
const char *DrawUtils::HERO_ARCHER_LEFT_SYMBOL = "<";
const char *DrawUtils::HERO_ARCHER_RIGHT_SYMBOL = ">";
#endif


void DrawUtils::init() {
    setlocale(LC_ALL, "");
    initscr();
    raw();
    noecho();
    curs_set(0);
    start_color();
    init_pair(BACKGROUND, COLOR_WHITE, COLOR_WHITE);
    init_pair(GAME_OVER_INFO, COLOR_BLACK, COLOR_WHITE);
    init_pair(SOLID_BARRIER, COLOR_BLACK, COLOR_BLACK);
    init_pair(WEAK_BARRIER, COLOR_CYAN, COLOR_CYAN);
    init_pair(RANDOM_WALK_ENEMY, COLOR_BLUE, COLOR_WHITE);
    init_pair(SMART_ENEMY, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(MIND_CONTROL, COLOR_WHITE, COLOR_BLUE);
    init_pair(HERO, COLOR_RED, COLOR_WHITE);
    init_pair(POTION, COLOR_WHITE, COLOR_GREEN);
}

void DrawUtils::showGameOver() {
    vector<const char *> strs = {"  __ _  __ _ _ __ ___   ___    _____   _____ _ __",
                                 " / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|",
                                 "| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |",
                                 " \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|",
                                 " |___/"};
    attron(COLOR_PAIR(GAME_OVER_INFO));
    for (int i = 0; i < strs.size(); ++i) {
#ifdef USE_UNICODE_CHARACTER
        mvprintw(MapUtils::nLines() / 2 - 3 + i, MapUtils::nCols() - 25, strs[i]);
#else
        mvprintw(MapUtils::nLines() / 2 - 3 + i, MapUtils::nCols() / 2 - 25, strs[i]);
#endif
    }
    attroff(COLOR_PAIR(GAME_OVER_INFO));
    mvprintw(MapUtils::nLines(), 2, "Press Big Q to Continue...                       ");
    refresh();
    while (getch() != 'Q') {
    }
    endwin();
}

void DrawUtils::pause() {
    mvprintw(MapUtils::nLines(), 2,
             "Game Paused, Press p to Continue                               ");
    refresh();
    while (getch() != 'p') {
    }
    mvprintw(MapUtils::nLines(), 1,
             "                                                               ");
    refresh();
}

void DrawUtils::draw() {
    for (int i = 0; i < MapUtils::nCols(); ++i) {
        for (int j = 0; j < MapUtils::nLines(); ++j) {
            drawAxis(i, j);
        }
    }

    mvprintw(0, 2, "HP: %d ATK: %d DEF: %d MindCtrl: %d SCORE: %d            ",
             MapUtils::myHero->healthPoint, MapUtils::myHero->arrowAttackVal,
             MapUtils::myHero->defendVal, MapUtils::myHero->nMindControl, MapUtils::myHero->score);

    mvprintw(MapUtils::nLines() - 1, 2, curEnemyInfo.c_str());

    refresh();
}

void DrawUtils::drawAxis(int x, int y) {
#ifdef USE_UNICODE_CHARACTER
    int drawX = 2 * x;
#else
    int drawX = x;
#endif
    Item *item = MapUtils::gameMap[x][y];
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

string DrawUtils::curEnemyInfo;

void DrawUtils::genCurEnemyInfo(Vulnerable &enemy) {
    string s = "Attack Enemy: (";
    auto aggressive = dynamic_cast<Aggressive *>(&enemy);
    if (aggressive) {
        s += "ATK=" + to_string(aggressive->attackVal) + ", ";
    }
    s += "DEF=" + to_string(enemy.defendVal) + ", ";
    s += "HP=" + to_string(enemy.healthPoint);
    s += ")                    ";
    curEnemyInfo = s;
}

