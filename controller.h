#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

const int FIRST_LINE_OFFSET = 70;
const int SCREEN_DIM = 300;

class Controller
{
public:
    Controller(QWidget *window);

    void renderScreen(QPainter &painter);

private:
    QWidget *window;

};

#endif // CONTROLLER_H
