#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QByteArray>

#define serverip "192.168.0.1"
#define port 80100


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
        tcpSocket.connectToHost(QHostAddress::LocalHost, port);
        nextBlockSize = 0;
    }
}

void MainWindow::setName(const int &index)
{
    this->iname = index;
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

}

void MainWindow::sendRequest()
{

}

void MainWindow::error()
{

}
