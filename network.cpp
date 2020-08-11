#include "network.h"

#include <QTcpServer>
#include <QTcpSocket>

Network::Network(int clientType)
{
    this->clientType = clientType;
}

// for server
void Network::startServer() {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(userConnected()));
    if (!tcpServer->listen(QHostAddress::Any, PORT)) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        return;
    }

    qDebug() << "TCPSocket listen on port 33333";
    qDebug() << QString::fromUtf8("Сервер запущен!");
}

void Network::userConnected()
{
    qDebug() << QString::fromUtf8("Клиент подключился!");
    clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(socketRead()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(clientDisconected()));
    clientSocket->write("hello, this is connected");
}

void Network::socketRead() {
    QByteArray data = clientSocket->readAll();
    qDebug() << "from client: " << data << Qt::endl;
    this->onDataRecieved(data);
}

void Network::clientDisconected() {
    qDebug() << "client disconnected"<< Qt::endl;
    clientSocket->deleteLater();
}

// for client
void Network::startClient() {
    mySocket = new QTcpSocket(this);
    mySocket->connectToHost(HOST_ADDR, PORT);
    qDebug() << "connected to server" << Qt::endl;

    connect(mySocket, SIGNAL(readyRead()), this, SLOT(clientSockReady()));
    connect(mySocket, SIGNAL(disconnected()), this, SLOT(clientSockDisconnected()));
}

void Network::clientSockReady() {
    QByteArray data = mySocket->readAll();
    qDebug() << "from server: " << data << Qt::endl;
    this->onDataRecieved(data);
}

QTcpSocket* Network::getSocketToSend() {
    if (this->clientType == HOST_TYPE) {
       return this->clientSocket;
    }
    return this->mySocket;
}

void Network::send(QString *message) {
    QTcpSocket *socket = this->getSocketToSend();
    socket->write(message->toLocal8Bit());
}

void Network::clientSockDisconnected() {
    mySocket->deleteLater();
}

