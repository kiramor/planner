#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kdatabase.h"

#include <QDebug>

MainWindow::MainWindow(KDataBase &dataBase, QWidget *parent) :
    QMainWindow(parent), DataBase(dataBase),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbTest1_clicked()
{
    DataBase.createDay(11);


    DataBase.printDay(11);
}

void MainWindow::on_sbDayIndex_valueChanged(int arg1)
{
    updateGuiForDay(arg1);
}

void MainWindow::clearGui()
{
    ui->labDayInfo->clear();

    ui->lwEvents->clear();
    ui->lwHobbies->clear();
    ui->lwHome->clear();
    ui->lwProjects->clear();
    ui->lwStudy->clear();
    ui->lwToDo->clear();
}

void MainWindow::updateGuiForDay(int dayIndex)
{
    if (DataBase.isDayExist(dayIndex))
    {
        ui->labDayInfo->setText("lalalaaaaaaaaaaa");

        //tasks
        for (const KTask& todo : DataBase.getDay(dayIndex)->getListToDo())
            ui->lwToDo->addItem(todo.Name);
    }
    else
        clearGui();
}

void MainWindow::on_lwToDo_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << "Cont menu requested for tasks!";
}
