#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWidget>

#include <QTcpServer>

const int PORT = 33333;
const QString HOST_ADDR = "127.0.0.1";

class Network : public QObject
{
    Q_OBJECT
public:
    Network();

    void startServer();
    void startClient();

public slots:
    // for server slots
    void userConnected();
    void socketRead();
    void clientDisconected();

    // for client slots
    void clientSockReady();
    void clientSockDisconnected();

private:
    // for server
    QTcpServer *tcpServer;
    QTcpSocket *clientSocket;

    // for client
    QTcpSocket *mySocket;
};

#endif // SERVER_H
