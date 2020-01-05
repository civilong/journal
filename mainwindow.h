#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDate>
#include <QTcpSocket>
#include <QDataStream>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();
    //xingming de hanshu
    int getName();
    QDate getDate();

    //tongxin xiangguan
    void connectToServer();


public slots:
    //jiemian xiangguan
    void setName(const int &index);

    void decDate();
    void setDate(const QDate &newDate);
    void incDate();

    void updateBox();

    //tongxinxiangguan
    void sendRequest();
    void error();

private:
    Ui::MainWindow *ui;
    int iname;
    QDate date;
    QTcpSocket tcpSocket;
    quint16 nextBlockSize;
};

#endif // MAINWINDOW_H
