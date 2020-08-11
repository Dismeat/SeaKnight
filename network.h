#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWidget>

#include <QTcpServer>

const int PORT = 33333;
const QString HOST_ADDR = "127.0.0.1";

const int HOST_TYPE = 0;
const int CLIENT_TYPE = 1;

class Network : public QObject
{
    Q_OBJECT
public:
    Network(int clientType);

    void startServer();
    void startClient();

    QTcpSocket *getSocketToSend();
    void send(QString *message);
    virtual void onDataRecieved(QByteArray data) = 0;

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

    // server or host
    int clientType;
};

#endif // SERVER_H
