#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

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
    MainWindow(QWidget *parent = nullptr, int client=HOST);
    ~MainWindow();

    void setClientType(int clientType);
    int getClientType();

protected:
    void paintEvent( QPaintEvent* event );
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_readyBtn_clicked();

private:
    Controller *controller;
    Ui::MainWindow *ui;

    // Client type HOST/CLIENT only
    int clientType;
};
#endif // MAINWINDOW_H
