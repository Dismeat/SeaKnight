#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "controller.h"
class Controller;

enum {
  HOST,
    CLIENT,
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setClientType(int clientType);
    int getClientType();

protected:
    void paintEvent( QPaintEvent* event );
    void mouseMoveEvent(QMouseEvent *event);

private:
    Controller *controller;
    Ui::MainWindow *ui;\

    // Client type HOST/CLIENT only
    int clientType;
};
#endif // MAINWINDOW_H
