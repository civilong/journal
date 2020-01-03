#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    ui->dateEdit->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}
