#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kdatabase.h"
#include "kjsontools.h"
#include "ktaskwindow.h"
#include <QDebug>

#include <QDialog>
#include <QCalendarWidget>


MainWindow::MainWindow(KDataBase &dataBase, QWidget *parent) :
    QMainWindow(parent), DataBase(dataBase), ui(new Ui::MainWindow), OpenDate(QDate::currentDate())
{
    ui->setupUi(this);

    ui->lwToDo->setDragDropMode(QAbstractItemView::DragDrop);
    ui->lwToDo->setDefaultDropAction(Qt::MoveAction);

    updateGuiForOpenDay();
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
    DataBase.createDummyDay(OpenDate);
    updateGuiForOpenDay();
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

//void MainWindow::updateGuiForDay(int dayIndex, QVector<KTask> &container, QListWidget *lw)
void MainWindow::updateGuiForOpenDay()
{
    clearGui();

    KDay* thisDay = DataBase.getDay(OpenDate);

    QString str = thisDay->getQDate().toString("  dddd, dd of MMMM, yyyy");
    ui->labDayInfo->setText(str);

    //tasks
    //QVector<KTask>& container = thisDay->getListToDo();

    updateTaskWidget(thisDay->getListToDo(), ui->lwToDo);
    //updateTaskWidget(container, lw);
    updateTaskWidget(thisDay->getListHomework(), ui->lwHome);
    updateTaskWidget(thisDay->getListStudy(), ui->lwStudy);
}

void MainWindow::updateTaskWidget(QVector<KTask> &container, QListWidget *lw)
{
    KDay::sortTasks(container);

    for (const KTask& todo : container)
    {
        QListWidgetItem *item = new QListWidgetItem(todo.Name);
        if (todo.Acomplished) item->setBackgroundColor(Qt::darkGreen);

        //item->setCheckState( todo.Acomplished ? Qt::Checked : Qt::Unchecked);
        lw->addItem(item);
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
    //QAction* blabla = m.addAction("Do blabla");
    m.addSeparator();

    QAction* selectedItem = m.exec(ui->lwToDo->mapToGlobal(pos));
    if (!selectedItem) return; //nothing was selected

    if (selectedItem == toggleDone)
    {
        int currentTask = row;
        if (DataBase.isDayExist(OpenDate))
        {
            KDay* thisDay = DataBase.getDay(OpenDate);
            if (currentTask < thisDay->getListToDo().size())
                //qDebug() <<"huh wanna toggle?";
                thisDay->getListToDo()[currentTask].toggleAcomplishedStatus();
            updateGuiForOpenDay();
        }
        else
            qDebug() << "!!!!!----------  OpenDay does not exist";
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

void MainWindow::on_pbCalendar_clicked()
{
    QDialog* m = new QDialog(this);
    m->setWindowTitle("Select date");

    QVBoxLayout* l = new QVBoxLayout(m);
        QCalendarWidget* cw = new QCalendarWidget(m);
    l->addWidget(cw);
    cw->setSelectedDate(OpenDate);


    QHBoxLayout* lh = new QHBoxLayout();

        QPushButton* pbOK = new QPushButton("Select", this);
        lh->addWidget(pbOK);

        QPushButton* cancel = new QPushButton(this);
        cancel->setText("cancel");
        lh->addWidget(cancel);

        /*
        QPushButton* pbThisDay = new QPushButton(this);
        pbThisDay->setText("back to the present");
        l->addWidget(pbThisDay);
        */
    l->addLayout(lh);


    QObject::connect(pbOK, &QPushButton::clicked, m, &QDialog::accept);
    QObject::connect(cancel, &QPushButton::clicked, m, &QDialog::reject);
    //QObject::connect(pbThisDay, &QPushButton::clicked, [&cw](){cw->setSelectedDate(QDate::currentDate());});

    m->exec();

    if (m->result()==QDialog::Accepted)
    {
        QDate d = cw->selectedDate();
        qDebug() << "User selected day:"<< d.toString();
        OpenDate = d;
        updateGuiForOpenDay();
    }

    delete m;
}

void MainWindow::on_pbToday_clicked()
{
   OpenDate = QDate::currentDate();
   updateGuiForOpenDay();
}

void MainWindow::on_pbToDo_clicked()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    KTaskWindow* tw = new KTaskWindow(thisDay->getListToDo(), this);
    tw->setWindowModality(Qt::WindowModal);
    QObject::connect(tw, &KTaskWindow::TaskWindowClosed, this, &MainWindow::updateGuiForOpenDay);
    tw->show();


}

void MainWindow::on_pbStudy_clicked()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    KTaskWindow* tw = new KTaskWindow(thisDay->getListStudy(), this);
    tw->setWindowModality(Qt::WindowModal);
    QObject::connect(tw, &KTaskWindow::TaskWindowClosed, this, &MainWindow::updateGuiForOpenDay);
    tw->show();

}

void MainWindow::on_pbHomework_clicked()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    KTaskWindow* tw = new KTaskWindow(thisDay->getListHomework(), this);
    tw->setWindowModality(Qt::WindowModal);
    QObject::connect(tw, &KTaskWindow::TaskWindowClosed, this, &MainWindow::updateGuiForOpenDay);
    tw->show();
}

