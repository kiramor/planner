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
    DataBase.createDay(1);
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
    clearGui();

    if (DataBase.isDayExist(dayIndex))
    {
        KDay* thisDay = DataBase.getDay(dayIndex);

        QString str = thisDay->getQDate().toString("  dddd, dd of MMMM, yyyy");
        ui->labDayInfo->setText(str);

        //tasks
        QVector<KTask>& container = thisDay->getListToDo();
        KDay::sortTasks(container);

        for (const KTask& todo : thisDay->getListToDo())
        {
            QListWidgetItem *item = new QListWidgetItem(todo.Name);
            if (todo.Acomplished) item->setBackgroundColor(Qt::darkGreen);

            //item->setCheckState( todo.Acomplished ? Qt::Checked : Qt::Unchecked);
            ui->lwToDo->addItem(item);
        }
    }
}

#include <QMenu>
void MainWindow::on_lwToDo_customContextMenuRequested(const QPoint &pos)
{
    QMenu m;
    int row = -1;

    //QString shownItemType;
    QListWidgetItem* temp = ui->lwToDo->itemAt(pos);

    QAction* toggleDone = 0;

    if (temp)
      {
        //menu triggered at a valid item
        row = ui->lwToDo->row(temp);

        m.addSeparator();
        toggleDone = m.addAction("Change done state");
      }
    m.addSeparator();
    QAction* blabla = m.addAction("Do blabla");
    m.addSeparator();

    QAction* selectedItem = m.exec(ui->lwToDo->mapToGlobal(pos));
    if (!selectedItem) return; //nothing was selected

    if (selectedItem == toggleDone)
    {
        int currentTask = row;
        int index = ui->sbDayIndex->value();
        if (DataBase.isDayExist(index))
        {
            KDay* thisDay = DataBase.getDay(index);
            if (currentTask < thisDay->getListToDo().size())
                thisDay->getListToDo()[currentTask].toggleAcomplishedStatus();
            updateGuiForDay(index);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    saveBase();
}

void MainWindow::on_actionLoad_triggered()
{
    loadBase();
}
