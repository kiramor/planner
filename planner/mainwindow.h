#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class KDataBase;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(KDataBase& dataBase, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbTest1_clicked();

    void on_sbDayIndex_valueChanged(int arg1);

    void on_lwToDo_customContextMenuRequested(const QPoint &pos);

private:
    KDataBase & DataBase;
    Ui::MainWindow *ui;


private:
    void clearGui();
    void updateGuiForDay(int dayIndex);

};

#endif // MAINWINDOW_H
