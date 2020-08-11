#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

#include "battlefield.h";
#include "network.h";

const int FIRST_LINE_OFFSET = 100;
const int SCREEN_DIM = 300;
const int LINE_STEP = SCREEN_DIM / 10;

const int FIRST_FIELD_OFSSET = 20;
const int SECOND_FIELD_OFFSET = 380;

enum FIELDS {
    FIRST_FIELD,
    SECOND_FIELD,
};

enum TURNS {
    PLACE_SHIPS,
    MY_TURN,
    ENIMIE_TURN,
};

class Controller : public Network{
    Q_OBJECT
public:
    Controller(QWidget *window, Ui::MainWindow *ui, int client);

    void drawField(QPainter &painter, int xOffset);
    void drawCells(QPainter *painter, int fieldType);
    void drawShipCell(QPainter *painter, QColor color, int xOffset, int yOffset, int x, int y);
    void drawMissCell(QPainter *painter, int xOffset, int yOffset, int x, int y);
    void renderScreen(QPainter &painter);

    void detectClickField(QPoint pos);
    QPoint parseClickFieldCoordinates(int fieldType, int x, int y);
    void readyBtnClicked();
    void showInfoMessage(QString messageTitle, QString messageContent);

    // from FIELDS enum parameter
    BattleField* getField(int fieldType);
    int getFieldXOffset(int fieldType);

    void placeToCell(int fieldType, int cellType, QPoint cell);

    void onDataRecieved(QByteArray data) override;

private:
    QWidget *window;
    Ui::MainWindow *ui;

    int currentGameStatus;

    BattleField *myShips;
    BattleField *enemyShips;

    // Client type HOST/CLIENT only
    int clientType;
};

#endif // CONTROLLER_H
