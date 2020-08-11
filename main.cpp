#include "mainwindow.h"

#include <QApplication>

#include "network.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr, HOST);
    w.show();

    MainWindow w1(nullptr, CLIENT);
    w1.show();

    return a.exec();
}
