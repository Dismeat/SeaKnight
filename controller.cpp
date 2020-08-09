#include "controller.h"
#include "qpainter.h"

#include "QDebug"
#include "QMouseEvent"

#include <iostream>


Controller::Controller(QWidget *window)
{
    this->window = window;
}

void Controller::renderScreen(QPainter &painter) {
    painter.drawRect(QRect(20, FIRST_LINE_OFFSET, 20 + SCREEN_DIM, FIRST_LINE_OFFSET + SCREEN_DIM));
    painter.drawLine(0, 0, this->window->width(), this->window->height() - 1);
}
