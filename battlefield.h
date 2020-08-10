#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QObject>
#include <QWidget>

const int BATTLE_SIZE = 10;
const int SHIPS_CELLS_TO_START = 17;

enum {
    CELL_NONE, // nothing cell
    CELL_SHIP, // ship cell
    CELL_MISS, // miss atack cell
    CELL_DAMAGED, // damaged ship cell
};

class BattleField
{
public:
    BattleField();
    ~BattleField();

    int ** getField();
    void setCell(int x, int y, int cellType);
    int getCell(int x, int y);

    // checkPlaced -> CELL_SHIP - to ships placed, CELL_DAMAGED - to game ended
    bool checkPlaced(int cellType);

private:
    int **battleField;
};

#endif // BATTLEFIELD_H
