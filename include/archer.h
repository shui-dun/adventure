#ifndef ADVENTURE_ARCHER_H
#define ADVENTURE_ARCHER_H

#include "move.h"
#include "attack.h"
#include "item.h"
#include <map>
#include <vector>

using namespace std;


class Archer : public Item, public Vulnerable, public Movable {
public:

    int arrowAttackVal;

    int direction;

    Archer(int xPos, int yPos, const char *symbol, chtype color, int healthPoint, int defendVal,
           unsigned int timeUnits, unsigned int curTimeUnit,
           CampEnum camp,
           int bulletAttackVal, int direction) :
            Item(xPos, yPos, symbol, color, camp),
            Vulnerable(healthPoint, defendVal),
            Movable(timeUnits, curTimeUnit),
            arrowAttackVal(bulletAttackVal), direction(direction) {}
};


class HeroArcher : public Archer {
private:
    void updateSymbol();

    static map<chtype, int> directMap;

    vector<Item *> findNearestEnemies();

    void mindControl();

public:
    chtype inputChar;

    int score;

    int nMindControl;

    HeroArcher(int xPos, int yPos);

    bool act() override;
};

class RandomWalkArcher : public Archer {
public:
    RandomWalkArcher(int xPos, int yPos);

    bool act() override;
};

class SmartArcher : public Archer {
private:
    bool aligned(Item &item);

public:
    SmartArcher(int xPos, int yPos);

    bool act() override;
};

class ArcherUtils {
public:
    static bool defaultMove(Archer *shooter, int newX, int newY);

    static bool defaultShoot(Archer *shooter, int newX, int newY);
};

#endif //ADVENTURE_ARCHER_H
