#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDate>

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
    //void setName(const int& index);
    //void setDate(const QString );

public slots:
    //void sendRequest(const int& index);
    //void sendRequest(const QString& date);

private:
    Ui::MainWindow *ui;
    int iname;
    QDate date;
};

#endif // MAINWINDOW_H
