#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

namespace Ui {
class MainWindow;
}

class KDataBase;
class KTask;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QDate openDate= QDate::currentDate();
public:
    MainWindow(KDataBase& dataBase, QWidget *parent = 0);
    ~MainWindow();

    bool saveBase();
    bool loadBase();

private slots:
    void on_pbTest1_clicked();

    void on_sbDayIndex_valueChanged(int arg1);

    void on_lwToDo_customContextMenuRequested(const QPoint &pos);

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_pbCalendar_clicked();

private:
    KDataBase & DataBase;
    Ui::MainWindow *ui;


private:
    void clearGui();
    void updateGuiForDay(int dayIndex);
    void updateTaskWidget(QVector<KTask> &container, QListWidget *lw);

};

#endif // MAINWINDOW_H
