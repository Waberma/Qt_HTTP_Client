#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
Client::Client(QWidget *parent) :
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->outTextEdit->setReadOnly(true);
}

Client::~Client()
{
    delete ui;
    emit stopTimer();
    secthread->wait();
    secthread->deleteLater();
}

void Client::on_startButton_clicked()
{
    if(ui->startButton->text() == "Start")
    {
        ui->startButton->setText("Stop");

        if(!(ui->serverAddresLine->text() != ""))
        {
            QMessageBox::critical(this, "Внимание", "Сервер не введен");
            return;
        }

        secthread = new SocketThread(ui->serverAddresLine->text(), this);
        connect(secthread, &SocketThread::sendHTTPQuery, this, &Client::take, Qt::DirectConnection);
        connect(this, &Client::stopTimer, secthread, &SocketThread::stop, Qt::DirectConnection);
        connect(secthread, &SocketThread::error, this, &Client::showError, Qt::DirectConnection);

        secthread->start();
        return;
    }
    if(ui->startButton->text() == "Stop")
    {
        ui->startButton->setText("Start");
        emit stopTimer();
        secthread->wait();
        secthread->deleteLater();
    }
}

void Client::take(QByteArray query)
{
    httpquery.push_back(query);
    for(auto el : httpquery)
    {
        ui->outTextEdit->append(el);
    }
    httpquery.clear();
}

void Client::on_clearBtn_clicked()
{
    ui->outTextEdit->clear();
}

void Client::showError()
{
    ui->outTextEdit->append("Can't connect");
}

QMenu *Client::getMenu()
{
    QMenu *menu = new QMenu("HttpClient");
    QAction *action = new QAction("Очистить");
    connect(action, &QAction::triggered, this, &Client::on_clearBtn_clicked);
    menu->addAction(action);
    return menu;
}
