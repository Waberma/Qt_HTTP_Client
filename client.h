#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QByteArray>
#include <QTcpSocket>
#include "socketthread.h"
#include "MenuInterface.h"
namespace Ui {
class Client;
}

class Client : public MenuWidgetInterface
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
signals:
    void stopTimer();
private slots:
    void on_startButton_clicked();

    void take(QByteArray query);

    void on_clearBtn_clicked();

    void showError();

private:
    Ui::Client *ui;
    QVector<QByteArray> httpquery;
    QTcpSocket *socket;
    QByteArray data;
    SocketThread *secthread;

    // MenuWidgetInterface interface
public:
    QMenu *getMenu();
};

#endif // CLIENT_H
