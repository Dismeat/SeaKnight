#include "mainwindow.h"

#include <QApplication>

#include "network.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Network *network = new Network();
    network->startServer();

    Network *client = new Network();
    client->startClient();

    return a.exec();
}
