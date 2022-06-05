#include "map.h"
#include "cursesw.h"
#include "barrier.h"
#include "boxer.h"
#include "potion.h"
#include "draw.h"
#include <thread>
#include <mutex>
#include <random>

using namespace std;

vector<vector<Item *>> MapUtils::gameMap;

HeroShooter *MapUtils::myHero;

bool MapUtils::gameOver;

mutex MapUtils::mapMutex;

mt19937 MapUtils::randEngine;

void MapUtils::init() {
    genWall();
    genRandomMap();
    createInitCharacters();
}

void MapUtils::genWall() {
    int lines = 26;
    int cols = 52;
    gameMap.assign(cols, vector<Item *>(lines, nullptr));
    for (int i = 0; i < lines; ++i) {
        gameMap[0][i] = new SolidBarrier(0, i);
        gameMap[cols - 1][i] = new SolidBarrier(cols - 1, i);
    }
    for (int i = 1; i < cols - 1; ++i) {
        gameMap[i][0] = new SolidBarrier(i, 0);
        gameMap[i][lines - 1] = new SolidBarrier(i, lines - 1);
    }
    myHero = new HeroShooter(cols - 2, lines - 2);
    gameMap[cols - 2][lines - 2] = myHero;
}

void MapUtils::genRandomMap() {
    // 除了这种点状地图，以后还要产生几种迷宫地图
    for (int i = 1; i < nCols() - 1; ++i) {
        for (int j = 1; j < nLines() - 1; ++j) {
            if (gameMap[i][j] != nullptr) {
                continue;
            }
            uniform_real_distribution<float> distribution(0.0, 1.0);
            double randVal = distribution(randEngine);
            if (randVal < 0.8) {
                continue;
            } else if (randVal < 0.9) {
                gameMap[i][j] = new SolidBarrier(i, j);
            } else {
                gameMap[i][j] = new WeakBarrier(i, j);
            }
        }
    }
}

void MapUtils::createInitCharacters() {
    for (int i = 0; i < 20; ++i) {
        createRandomCharacter();
    }
}


void MapUtils::createRandomCharacter() {
    int xPos, yPos;
    uniform_int_distribution<int> xDistribution(1, nCols() - 2);
    uniform_int_distribution<int> yDistribution(1, nLines() - 2);
    while (true) {
        xPos = xDistribution(randEngine);
        yPos = yDistribution(randEngine);
        if (gameMap[xPos][yPos] == nullptr) {
            break;
        }
    }
    Item *item;
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
    gameMap[xPos][yPos] = item;
}


bool MapUtils::isAxisLegal(int xPos, int yPos) {
    return xPos >= 0 && xPos < nCols() && yPos >= 0 && yPos < nLines();
}

pair<int, int> MapUtils::nextPosOfDirection(Item &item, int direction) {
    int newX = item.xPos, newY = item.yPos;
    if (direction == 0) {
        newY -= 1;
    } else if (direction == 1) {
        newY += 1;
    } else if (direction == 2) {
        newX -= 1;
    } else {
        newX += 1;
    }
    return {newX, newY};
}

bool MapUtils::shouldMove(Movable &movable) {
    movable.curTimeUnit = (movable.curTimeUnit + 1) % movable.timeUnits;
    return movable.curTimeUnit == 0;
}

void MapUtils::moveAllCharacters() {
    for (int i = 1; i < nCols() - 1; ++i) {
        for (int j = 1; j < nLines() - 1; ++j) {
            auto movable = dynamic_cast<Movable *>(gameMap[i][j]);
            if (movable == nullptr)
                continue;
            if (dynamic_cast<HeroShooter *>(movable))
                continue;
            if (!shouldMove(*movable))
                continue;
            movable->act();
        }
    }
}

void MapUtils::moveMyHero() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(200));
        chtype inputChar = getch();
        mapMutex.lock();
        if (gameOver) {
            mapMutex.unlock();
            return;
        }
        myHero->inputChar = inputChar;
        myHero->act();
        mapMutex.unlock();
    }
}

void MapUtils::moveToPos(Item &item, int newX, int newY) {
    gameMap[item.xPos][item.yPos] = nullptr;
    gameMap[newX][newY] = &item;
    item.xPos = newX;
    item.yPos = newY;
}

int MapUtils::nLines() {
    return int(gameMap[0].size());
}

int MapUtils::nCols() {
    return int(gameMap.size());
}


