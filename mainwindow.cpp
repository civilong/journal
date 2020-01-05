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
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_3);

    //xuyao genju fuwuqi gaixie
    forever
    {
        int num = 0;
        if(nextBlockSize == 0)
        {
            if(tcpSocket.bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in>>nextBlockSize;
        }
        if(nextBlockSize == 0xFFFF)
        {
            //closeConnection();
            break;
        }
        if(tcpSocket.bytesAvailable() < nextBlockSize)
        {
            break;
        }

        QString summary, plan;
        if(num == 0)
        {
            in>>summary;
            ui->summaryEdit->setText(str);
        }
        else if(num == 1)
        {
            in>>plan;
            ui->planEdit->setText(str);
            if()
        }

        num++;
        nextBlockSize = 0;
    }

}

void MainWindow::sendRequest()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out<<quint16(0)<<quint8('S')<<quint16(getName())<<getDate().toString();
    out.device()->seek(0);
    out<<quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);
}

void MainWindow::error()
{

}
