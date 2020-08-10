#include "battlefield.h"
#include "QDebug"

BattleField::BattleField() {
    this->battleField = new int*[BATTLE_SIZE];
    for (int i = 0; i < BATTLE_SIZE; i++) {
        this->battleField[i] = new int[BATTLE_SIZE];
    }

    for (int i = 0; i < BATTLE_SIZE; i++) {
        for (int j = 0; j < BATTLE_SIZE; j++) {
            this->battleField[i][j] = CELL_NONE;
        }
    }
}

int **BattleField::getField() {
    return this->battleField;
}

void BattleField::setCell(int x, int y, int cellType) {
    this->battleField[x][y] = cellType;
}

int BattleField::getCell(int x, int y) {
    return this->battleField[x][y];
}

bool BattleField::checkPlaced(int cellType) {
    int shipsCellsCounter = 0;
    for (int i = 0; i < BATTLE_SIZE; i++) {
        for (int j = 0; j < BATTLE_SIZE; j++) {
            if (this->battleField[i][j] == cellType) {
                shipsCellsCounter++;
            }
        }
    }

    return (shipsCellsCounter == SHIPS_CELLS_TO_START);
}

BattleField::~BattleField() {
    for (int i = 0; i < BATTLE_SIZE; i++) {
        delete[] this->battleField[i];
    }
    delete[] this->battleField;
}
