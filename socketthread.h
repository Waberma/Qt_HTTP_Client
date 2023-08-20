//#ifndef SOCKETTHREAD_H
//#define SOCKETTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QTimer>

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(QString, QObject *parent);
    ~SocketThread();
    void run();
private:
    QTcpSocket *socket;
    QByteArray data;
    QString server;
    QTimer *timer;
signals:
    void sendHTTPQuery(QByteArray);
    void error();
public slots:
    void slotRead();

    void slotConnected();

    void showHTTPQuery();

    void slotTimerAlarm();

    void stop();
};

//#endif // SOCKETTHREAD_H
