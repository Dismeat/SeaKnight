#include "controller.h"
#include "qpainter.h"

#include "QDebug"
#include "QMouseEvent"

#include <iostream>


Controller::Controller(QWidget *window)
{
    this->window = window;
}

void Controller::drawShipCell(QPainter *painter, int x, int y) {}

void Controller::drawField(QPainter &painter, int xOffset) {
    int currentLineStart = 0;
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

}

void Controller::renderScreen(QPainter &painter) {
    this->drawField(painter, FIRST_FIELD_OFSSET);
    this->drawField(painter, SECOND_FIELD_OFFSET);
}
