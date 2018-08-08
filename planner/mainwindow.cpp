#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kdatabase.h"
#include "kjsontools.h"

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

bool MainWindow::saveBase()
{
    QString fileName = "d:/planner/database.json";

    QJsonObject json;
    DataBase.writeToJson(json);

    bool bOK = SaveJsonToFile(json, fileName);
    qDebug() << "Write result:" << bOK;
    return bOK;
}

bool MainWindow::loadBase()
{
    QString fileName = "d:/planner/database.json";

    QJsonObject json;
    bool bOK = LoadJsonFromFile(json, fileName);
    qDebug() << "Read result:"<< bOK;
    DataBase.readFromJson(json);
    return bOK;
}

void MainWindow::on_pbTest1_clicked()
{
    DataBase.createDay(2);
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
        {
            QListWidgetItem *item = new QListWidgetItem(todo.Name);
            if (todo.Acomplished) item->setBackgroundColor(Qt::green);
            item->setCheckState( todo.Acomplished ? Qt::Checked : Qt::Unchecked);
            ui->lwToDo->addItem(item);

        }
    }
    else
        clearGui();
}

void MainWindow::on_lwToDo_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << "Cont menu requested for tasks!";
}

void MainWindow::on_actionSave_triggered()
{
    saveBase();
}

void MainWindow::on_actionLoad_triggered()
{
    loadBase();
}
