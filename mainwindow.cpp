#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

#include "QDebug"
#include "QMouseEvent"

#include "controller.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->controller = new Controller(this);

    this->repaint();
}

void MainWindow::paintEvent( QPaintEvent* event ) {
    Q_UNUSED( event );

    QPainter painter(this);

    this->controller->renderScreen(painter);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "Left mouse click!" << endl;
    }
}

void MainWindow::setClientType(int clientType) {
    this->clientType = clientType;
}

int MainWindow::getClientType() {
    return this->clientType;
}

MainWindow::~MainWindow()
{
    delete ui;
}

