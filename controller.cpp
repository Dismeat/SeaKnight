#include "controller.h"
#include "qpainter.h"

#include "QDebug"
#include "QMouseEvent"
#include "QLine"
#include "QPointF"

#include <iostream>

Controller::Controller(QWidget *window)
{
    this->window = window;

    this->myShips = new BattleField();
    this->enemyShips = new BattleField();

    this->currentGameStatus = PLACE_SHIPS;
    this->myShips->getField()[3][3] = CELL_SHIP;
    this->myShips->getField()[5][5] = CELL_MISS;
    this->enemyShips->getField()[3][3] = CELL_DAMAGED;
}

int Controller::getFieldXOffset(int fieldType) {
    if (fieldType == FIRST_FIELD) {
        return FIRST_FIELD_OFSSET;
    }
    return SECOND_FIELD_OFFSET;
}

void Controller::drawCells(QPainter *painter, int fieldType) {
    int xOffset = this->getFieldXOffset(fieldType);
    int yOffset = FIRST_LINE_OFFSET;

    BattleField *currentField = this->getField(fieldType);
    for (int i = 0; i < BATTLE_SIZE; i++) {
        for (int j = 0; j < BATTLE_SIZE; j++) {
            switch(currentField->getField()[i][j]) {
                case CELL_SHIP:
                    this->drawShipCell(painter, Qt::blue, xOffset, yOffset, i, j);
                    break;
                case CELL_DAMAGED:
                    this->drawShipCell(painter, Qt::red, xOffset, yOffset, i, j);
                    break;
                case CELL_MISS:
                    this->drawMissCell(painter, xOffset, yOffset, i, j);
                    break;
            }
        }
    }
}

void Controller::drawShipCell(QPainter *painter, QColor color, int xOffset, int yOffset, int x, int y) {
    painter->setPen(color);
    painter->drawLine(
                QLine(
                    xOffset + LINE_STEP * x,
                    yOffset + LINE_STEP * y,
                    xOffset + LINE_STEP * (x + 1),
                    yOffset + LINE_STEP * (y + 1)
                    )
                );

    painter->drawLine(
                QLine(
                    xOffset + LINE_STEP * (x+1),
                    yOffset + LINE_STEP * y,
                    xOffset + LINE_STEP * x,
                    yOffset + LINE_STEP * (y + 1)
                    )
                );
}

void Controller::drawMissCell(QPainter *painter, int xOffset, int yOffset, int x, int y) {
    painter->setPen(Qt::black);
    painter->drawEllipse(
                    QPointF(
                        xOffset + LINE_STEP * x +LINE_STEP / 2,
                        yOffset + + LINE_STEP * y + LINE_STEP / 2
                    ),
                    LINE_STEP / 4,
                    LINE_STEP / 4
                );
}

void Controller::placeToCell(int fieldType, int cellType, QPoint cell) {
    this->getField(fieldType)->setCell(cell.x(), cell.y(), cellType);

    this->window->update();
}

QPoint Controller::parseClickFieldCoordinates(int fieldType, int x, int y) {
    int xOffset = this->getFieldXOffset(fieldType);
    int yOffset = FIRST_LINE_OFFSET;

    QPoint *point = new QPoint(
                ((x - xOffset) / LINE_STEP),
                ((y - yOffset) / LINE_STEP)
            );

    return *point;
}

void Controller::detectClickField(QPoint pos) {
    int x = pos.x();
    int y = pos.y();
    if (
            (x >= FIRST_FIELD_OFSSET) &&
            (x <= FIRST_FIELD_OFSSET + SCREEN_DIM) &&
            (y >= FIRST_LINE_OFFSET) &&
            (y <= FIRST_LINE_OFFSET + SCREEN_DIM)
       ) {

        // if placing ships on the game start
        if (this->currentGameStatus == PLACE_SHIPS) {
            QPoint coords = this->parseClickFieldCoordinates(FIRST_FIELD, x, y);

            // if clicked cell == ship, change ship cell to empty cell
            int cellType = CELL_SHIP;
            if (this->myShips->getCell(coords.x(), coords.y()) == CELL_SHIP) {
                cellType = CELL_NONE;
            }

            this->placeToCell(
                        FIRST_FIELD,
                        cellType,
                        coords
                    );
        }
    }

    if (
            (x >= SECOND_FIELD_OFFSET) &&
            (x <= SECOND_FIELD_OFFSET + SCREEN_DIM) &&
            (y >= FIRST_LINE_OFFSET) &&
            (y <= FIRST_LINE_OFFSET + SCREEN_DIM)
       ) {
        qDebug() << "enemy ships";
    }
}

BattleField* Controller::getField(int fieldType) {
    switch (fieldType) {
        case FIRST_FIELD:
            return myShips;
        case SECOND_FIELD:
            return enemyShips;
    }

    return nullptr;
}

void Controller::drawField(QPainter &painter, int xOffset) {
    int currentLineStart = 0;
    painter.setPen(Qt::black);
    for (int i = 0; i < 10; i ++) {
        painter.drawLine(
                    QLine(xOffset + currentLineStart,
                          FIRST_LINE_OFFSET,
                          xOffset+currentLineStart,
                          FIRST_LINE_OFFSET + SCREEN_DIM)
                    );

        painter.drawLine(
                    QLine(xOffset,
                          FIRST_LINE_OFFSET + currentLineStart,
                          xOffset + SCREEN_DIM,
                          FIRST_LINE_OFFSET + currentLineStart)
                    );

        currentLineStart += LINE_STEP;
    }

    painter.drawLine(
                QLine(xOffset + currentLineStart,
                      FIRST_LINE_OFFSET,
                      xOffset+currentLineStart,
                      FIRST_LINE_OFFSET + SCREEN_DIM)
                );

    painter.drawLine(
                QLine(xOffset,
                      FIRST_LINE_OFFSET + currentLineStart,
                      xOffset + SCREEN_DIM,
                      FIRST_LINE_OFFSET + currentLineStart)
                );

    this->drawCells(&painter, FIRST_FIELD);
    this->drawCells(&painter, SECOND_FIELD);
}

void Controller::renderScreen(QPainter &painter) {
    this->drawField(painter, FIRST_FIELD_OFSSET);
    this->drawField(painter, SECOND_FIELD_OFFSET);
}
