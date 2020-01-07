#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

#define serverip "127.0.0.1"
#define port 10087


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    iname = 0;
    ui->setupUi(this);
    ui->nameBox->addItem(tr("姓名"));
    ui->nameBox->addItem(tr("杭旭"));
    ui->nameBox->addItem(tr("王志远"));
    ui->nameBox->addItem(tr("吴家豪"));
    ui->nameBox->addItem(tr("张浩康"));
    ui->nameBox->addItem(tr("赵帅旗"));
    ui->nameBox->addItem(tr("邹伟"));

    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setDate(QDate)));
    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->nameBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setName(int)));
    connect(ui->yestButton, SIGNAL(clicked()), this, SLOT(decDate()));
    connect(ui->tomoButton, SIGNAL(clicked()), this, SLOT(incDate()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(updateBox()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getName()
{
    return this->iname;
}

QDate MainWindow::getDate()
{
    return this->date;
}

void MainWindow::connectToServer()
{
    if(this->iname != 0)
    {
        tcpSocket.abort();
        tcpSocket.connectToHost(serverip, port);
        nextBlockSize = 0;
    }
}

void MainWindow::setName(const int &index)
{
    this->iname = index;
    qDebug("The name is set as:%d", index);
    connectToServer();
}

void MainWindow::decDate()
{
    QDate curr = getDate();
    QDate tmp = curr.addDays(-1);
    ui->dateEdit->setDate(tmp);
}

void MainWindow::setDate(const QDate &newDate)
{
    this->date = newDate;
    qDebug("The time is set as:%s", newDate.toString());
    connectToServer();
}

void MainWindow::incDate()
{
    QDate curr = getDate();
    QDate tmp = curr.addDays(1);
    ui->dateEdit->setDate(tmp);
}

void MainWindow::updateBox()
{
    qDebug("Get reply!");
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_3);
    QString reply;
    in>>reply;
    ui->summaryEdit->setText(reply);
}

void MainWindow::sendRequest()
{
    qDebug("Start send request");
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out<<getDate().toString();
    //out<<quint16(0)<<quint8('S')<<quint16(getName())<<getDate().toString();
    //out.device()->seek(0);
    //out<<quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);
}

void MainWindow::error()
{

}
