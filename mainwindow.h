#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMainWindow"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
void connectDB();// это созданный нами слот для выбора и подключения к базе данных
void inputtoDB(); //для ввода данных в базу данных
void outputfromDB(); //для получения данных из базы данных

};
#endif // MAINWINDOW_H


