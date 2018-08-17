#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QListWidget>


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
    MainWindow(KDataBase& dataBase, QWidget *parent = 0);
    ~MainWindow();

    bool saveBase();
    bool loadBase();

private slots:
    void on_pbTest1_clicked();
    void on_lwToDo_customContextMenuRequested(const QPoint &pos);
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_pbCalendar_clicked();
    void on_pbToday_clicked();
    void on_pbToDo_clicked();

    void on_pbStudy_clicked();

    void on_pbHomework_clicked();

private:
    KDataBase & DataBase;
    Ui::MainWindow *ui;

    QDate OpenDate;

private slots:
    void updateGuiForOpenDay();


    void on_lwStudy_itemDoubleClicked(QListWidgetItem *item);
    void on_lwStudy_itemClicked(QListWidgetItem *item);


    void on_lwToDo_itemDoubleClicked(QListWidgetItem *item);

    void on_lwHome_itemDoubleClicked(QListWidgetItem *item);

private:
    void clearGui();    
    void updateTaskWidget(QVector<KTask> &container, QListWidget *lw);


};

#endif // MAINWINDOW_H
