#include "socketthread.h"
#include <QMessageBox>
SocketThread::SocketThread(QString server, QObject *parent) :
    QThread (parent)
{
    this->server = server;
}

SocketThread::~SocketThread()
{
    socket->disconnectFromHost();
    socket->deleteLater();
}

void SocketThread::run()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()), Qt::DirectConnection);
    timer->start(3500); // И запустим таймер
    exec();
}

void SocketThread::slotRead()
{
    data.append(socket->readAll());
}

void SocketThread::slotConnected()
{
    socket->write("GET / HTTP/1.0\r\n\r\n");
}

void SocketThread::showHTTPQuery()
{
    if(socket->state() == QTcpSocket::UnconnectedState)
    {
        emit sendHTTPQuery(data);
        data.clear();
        socket->write("GET / HTTP/1.0\r\n\r\n");
    }
}

void SocketThread::slotTimerAlarm()
{
    socket = new QTcpSocket();
    connect(socket,&QTcpSocket::connected,this,&SocketThread::slotConnected, Qt::DirectConnection);
    connect(socket,&QTcpSocket::readyRead,this,&SocketThread::slotRead, Qt::DirectConnection);
    connect(socket, &QTcpSocket::stateChanged, this, &SocketThread::showHTTPQuery, Qt::DirectConnection);
    socket->connectToHost(server,80);
    if(socket->state() == QTcpSocket::HostLookupState)
        emit error();
}

void SocketThread::stop()
{
    quit();
}
