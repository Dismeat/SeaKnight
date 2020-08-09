#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "controller.h"
class Controller;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent( QPaintEvent* event );
    void mouseMoveEvent(QMouseEvent *event);

private:
    Controller *controller;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
