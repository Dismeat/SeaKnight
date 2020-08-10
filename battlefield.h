#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QObject>
#include <QWidget>

const int BATTLE_SIZE = 10;

enum {
    CELL_NONE, // nothing cell
    CELL_SHIP, // ship cell
    CELL_MISS, // miss atack cell
};

class BattleField
{
public:
    BattleField();
    ~BattleField();
private:
    int **battleField;
};

#endif // BATTLEFIELD_H
