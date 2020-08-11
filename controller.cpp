#include "controller.h"
#include "qpainter.h"

#include "QDebug"
#include "QMouseEvent"
#include "QLine"
#include "QMessageBox"
#include "QPointF"
#include "QString"
#include "controller.h"

#include <iostream>
#include <stdio.h>

Controller::Controller(QWidget *window, Ui::MainWindow *ui, int client) : Network(client)
{
    this->window = window;
    this->ui = ui;
    this->clientType = client;

    this->myShips = new BattleField();
    this->enemyShips = new BattleField();

    this->currentGameStatus = PLACE_SHIPS;
    this->shipsReady = false;

    if (this->clientType == HOST) {
        this->startServer();
    } else {
        this->startClient();
    }
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
    if ((x >= FIRST_FIELD_OFSSET) &&
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

    if ((x >= SECOND_FIELD_OFFSET) &&
        (x <= SECOND_FIELD_OFFSET + SCREEN_DIM) &&
        (y >= FIRST_LINE_OFFSET) &&
        (y <= FIRST_LINE_OFFSET + SCREEN_DIM)
       ) {
        if (this->currentGameStatus == MY_TURN) {
            QPoint coords = this->parseClickFieldCoordinates(SECOND_FIELD, x, y);

            QString message = QString("%1|%2|%3").arg(coords.x()).arg(coords.y()).arg("F");
            this->send(&message);
        }
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

void Controller::setGameStatus(int gameStatus) {
    this->currentGameStatus = gameStatus;

    if (currentGameStatus == MY_TURN) {
        this->ui->infoLabel->setText("Сделайте свой ход!");
        return;
    }
    this->ui->infoLabel->setText("Ждем пока походит противник");
}

void Controller::startGameIfNeed() {
    if (this->shipsReady && this->oponentReady) {
        if (this->clientType == HOST) {
            this->setGameStatus(MY_TURN);
            return;
        }

        this->setGameStatus(ENIMIE_TURN);
    }
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

void Controller::readyBtnClicked() {
    if (this->currentGameStatus == PLACE_SHIPS) {
        if (this->myShips->checkPlaced(CELL_SHIP)) {
            this->showInfoMessage(QString("Корабли растановлены правильно!"),
                                  QString("Начинаем игру")
                                  );

            QString *ready = new QString("ready");
            this->send(ready);

            this->shipsReady = true;
            this->ui->infoLabel->setText("Ждем соперника!");
            this->ui->readyBtn->setDisabled(true);

            // start game if opponent ready or wait them
            this->startGameIfNeed();
            return;
        }
        this->showInfoMessage(QString("Ошибка!"),
                              QString("Неправильно раставлены корабли")
                              );
        return;
    }
}

void Controller::showInfoMessage(QString messageTitle, QString messageContent) {
    QMessageBox msgBox;
    msgBox.setText(messageTitle);
    msgBox.setInformativeText(messageContent);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
}

void Controller::onDataRecieved(QByteArray data) {
   QString result = QString(data);
   if (result == "ready") {
        this->oponentReady = true;
        this->startGameIfNeed();
   }
   // p|p|c - command format
   if (result.size() == 5) {
        int pos1 = result.at(0).unicode() - 48;
        int pos2 = result.at(2).unicode() - 48;
        char command = result.at(4).unicode();
        qDebug() << pos1 << pos2 << command << Qt::endl;

        // taking fire
        if (command == 'F') {
            int cell = this->myShips->getCell(pos1, pos2);
            QString message;
            switch(cell) {
                case CELL_SHIP:
                    message = QString("%1|%2|%3").arg(pos1).arg(pos2).arg("D");
                    this->placeToCell(FIRST_FIELD, CELL_DAMAGED, QPoint(pos1, pos2));
                    break;
                case CELL_NONE:
                case CELL_MISS:
                    message = QString("%1|%2|%3").arg(pos1).arg(pos2).arg("M");
                    this->placeToCell(FIRST_FIELD, CELL_MISS, QPoint(pos1, pos2));
                    this->flipTurn();
                break;
            }
            this->send(&message);
        }

        // place cells to enemy field
        if (command == 'D' || command == 'M') {
            int currentCellType = command == 'D' ? CELL_DAMAGED : CELL_MISS;
            this->placeToCell(SECOND_FIELD, currentCellType, QPoint(pos1, pos2));

            if (command == 'M') {
                this->flipTurn();
            }
        }

        if (this->myShips->checkPlaced(CELL_DAMAGED)) {
            // game end
            this->showInfoMessage("Вы проиграли!", "Вы проиграли попробуйте сыграть еще раунд!");
        }
        if (this->enemyShips->checkPlaced(CELL_DAMAGED)) {
            // game end
            this->showInfoMessage("Вы выиграли!", "Ура, вы выиграли!");
        }

   }
}

void Controller::flipTurn() {
    if (this->currentGameStatus == MY_TURN) {
        this->currentGameStatus = ENIMIE_TURN;
        this->ui->infoLabel->setText("Ждем пока противник походит!");
    } else {
        this->currentGameStatus = MY_TURN;
        this->ui->infoLabel->setText("Сделайте свой ход!");
    }
}

void Controller::renderScreen(QPainter &painter) {
    this->drawField(painter, FIRST_FIELD_OFSSET);
    this->drawField(painter, SECOND_FIELD_OFFSET);
}
