#include "map.h"
#include "cursesw.h"
#include "barrier.h"
#include "swordsman.h"
#include "potion.h"
#include "draw.h"
#include <thread>
#include <mutex>
#include <random>
#include <queue>
#include <unordered_set>

using namespace std;

vector<vector<Item *>> MapUtils::gameMap;

HeroArcher *MapUtils::myHero;

bool MapUtils::gameOver;

mutex MapUtils::mapMutex;

mt19937 MapUtils::randEngine;

void MapUtils::init() {
    genWall();
    if (uniform_real_distribution<double>(0, 1.0)(randEngine) < 0.0) {
        genRandomMap();
    } else {
        genRecursiveSegmentationMap(1, 1, nCols() - 2, nLines() - 2);
    }
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
}

void MapUtils::genRandomMap() {
    for (int i = 1; i < nCols() - 1; ++i) {
        for (int j = 1; j < nLines() - 1; ++j) {
            if (gameMap[i][j]) {
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
    int xPos = 1, yPos = 1;
    while (gameMap[xPos][yPos]) {
        xPos++;
    }
    myHero = new HeroArcher(xPos, yPos);
    gameMap[xPos][yPos] = myHero;

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
        if (!gameMap[xPos][yPos]) {
            break;
        }
    }
    Item *item;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    double randVal = distribution(randEngine);
    if (randVal < 0.35) {
        item = new RandomWalkSwordsman(xPos, yPos);
    } else if (randVal < 0.4) {
        item = new SmartSwordsman(xPos, yPos);
    } else if (randVal < 0.7) {
        item = new RandomWalkArcher(xPos, yPos);
    } else if (randVal < 0.75) {
        item = new SmartArcher(xPos, yPos);
    } else if (randVal < 0.8125) {
        item = new MindControlPotion(xPos, yPos);
    } else if (randVal < 0.875) {
        item = new StrengthenPotion(xPos, yPos);
    } else if (randVal < 0.9375) {
        item = new DefendPotion(xPos, yPos);
    } else {
        item = new CurePotion(xPos, yPos);
    }
    gameMap[xPos][yPos] = item;
}


bool MapUtils::isAxisLegal(int xPos, int yPos) {
    return xPos >= 0 && xPos < nCols() && yPos >= 0 && yPos < nLines();
}

pair<int, int> MapUtils::nextPosOfDirection(Item &item, int direction) {
    return nextPosOfDirection(item.xPos, item.yPos, direction);
}

pair<int, int> MapUtils::nextPosOfDirection(int x, int y, int direction) {
    int newX = x, newY = y;
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
            if (!movable)
                continue;
            if (dynamic_cast<HeroArcher *>(movable))
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


void MapUtils::genRecursiveSegmentationMap(int xFrom, int yFrom, int xTo, int yTo) {
    if (xTo - xFrom <= 1 || yTo - yFrom <= 1) {
        return;
    }
    int xMid = uniform_int_distribution<int>(xFrom + 1, xTo - 1)(randEngine);
    int yMid = uniform_int_distribution<int>(yFrom + 1, yTo - 1)(randEngine);
    genLineOfWall(yFrom, yMid, xMid, false);
    genLineOfWall(yMid + 1, yTo, xMid, false);
    genLineOfWall(xFrom, xMid - 1, yMid, true);
    genLineOfWall(xMid + 1, xTo, yMid, true);
    genRecursiveSegmentationMap(xFrom, yFrom, xMid - 1, yMid - 1);
    genRecursiveSegmentationMap(xMid + 1, yFrom, xTo, yMid - 1);
    genRecursiveSegmentationMap(xFrom, yMid + 1, xMid - 1, yTo);
    genRecursiveSegmentationMap(xMid + 1, yMid + 1, xTo, yTo);
}

void MapUtils::genLineOfWall(int fromY, int toY, int x, bool horizontal) {
    bool solid = uniform_int_distribution<int>(0, 1)(randEngine) == 1;
    uniform_real_distribution<double> d(0, 1.0);
    double emptyProb = 0.3;
    if (!horizontal && !solid) {
        for (int i = fromY; i <= toY; i++) {
            if (d(randEngine) > emptyProb) {
                gameMap[x][i] = new WeakBarrier(x, i);
            }
        }
    } else if (!horizontal && solid) {
        for (int i = fromY; i <= toY; i++) {
            if (d(randEngine) > emptyProb) {
                gameMap[x][i] = new SolidBarrier(x, i);
            }
        }
    } else if (horizontal && !solid) {
        for (int i = fromY; i <= toY; i++) {
            if (d(randEngine) > emptyProb) {
                gameMap[i][x] = new WeakBarrier(i, x);
            }
        }
    } else {
        for (int i = fromY; i <= toY; i++) {
            if (d(randEngine) > emptyProb) {
                gameMap[i][x] = new SolidBarrier(i, x);
            }
        }
    }
    int holePos = uniform_int_distribution<int>(fromY, toY)(randEngine);
    if (!horizontal) {
        delete gameMap[x][holePos];
        gameMap[x][holePos] = nullptr;
    } else {
        delete gameMap[holePos][x];
        gameMap[holePos][x] = nullptr;
    }
}

int MapUtils::locatedAtDirection(Item &me, int destX, int destY) {
    if (destX == me.xPos) {
        if (destY < me.yPos)
            return 0;
        else
            return 1;
    } else {
        if (destX < me.xPos)
            return 2;
        else
            return 3;
    }
}

