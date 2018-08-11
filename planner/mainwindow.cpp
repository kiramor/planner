#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kdatabase.h"
#include "kjsontools.h"
#include <QDebug>

#include <QDialog>
#include <QCalendarWidget>

MainWindow::MainWindow(KDataBase &dataBase, QWidget *parent) :
    QMainWindow(parent), DataBase(dataBase),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lwToDo->setDragDropMode(QAbstractItemView::DragDrop);
    ui->lwToDo->setDefaultDropAction(Qt::MoveAction);
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
    //updateGuiForDay(arg1, DataBase.getDay(arg1)->getListToDo(), ui->lwToDo);
    updateGuiForDay(arg1);
    //updateGuiForDay(arg1, DataBase.getDay(arg1)->getListHomework(), ui->lwHome);
    //updateGuiForDay(arg1, DataBase.getDay(arg1)->getListStudy(), ui->lwStudy);
    //int day, month, year;
    //QDate d;
    //KDataBase::IndexToDate(arg1, day, month, year);


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
void MainWindow::updateGuiForDay(int dayIndex)
{
    clearGui();
    qDebug() <<"updating day with index:" <<dayIndex;

    if (DataBase.isDayExist(dayIndex))
    {
        KDay* thisDay = DataBase.getDay(dayIndex);

        QString str = thisDay->getQDate().toString("  dddd, dd of MMMM, yyyy");
        ui->labDayInfo->setText(str);

        //tasks
        //QVector<KTask>& container = thisDay->getListToDo();

        updateTaskWidget(thisDay->getListToDo(), ui->lwToDo);
        //updateTaskWidget(container, lw);
        updateTaskWidget(thisDay->getListHomework(), ui->lwHome);
        updateTaskWidget(thisDay->getListStudy(), ui->lwStudy);
    }
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

void MainWindow::on_pbCalendar_clicked()
{
    QDialog* m = new QDialog(this);
    m->setWindowTitle("Select date");

    QVBoxLayout* l = new QVBoxLayout(m);
        QCalendarWidget* cw = new QCalendarWidget(m);
    l->addWidget(cw);
    cw->setSelectedDate(openDate);

    QHBoxLayout* lh = new QHBoxLayout();
        QPushButton* cancel = new QPushButton(this);
        cancel->setText("cancel");
        lh->addWidget(cancel);
        QPushButton* pbOK = new QPushButton("Select", this);
        lh->addWidget(pbOK);
        QPushButton* pbThisDay = new QPushButton(this);
        pbThisDay->setText("back to the present");
        l->addWidget(pbThisDay);
    l->addLayout(lh);


    QObject::connect(pbOK, &QPushButton::clicked, m, &QDialog::accept);
    QObject::connect(cancel, &QPushButton::clicked, m, &QDialog::reject);
    QObject::connect(pbThisDay, &QPushButton::clicked, [&cw](){cw->setSelectedDate(QDate::currentDate());});

    m->exec();

    if (m->result()==QDialog::Accepted)
    {
        QDate d = cw->selectedDate();
        qDebug() << "Papa selected"<< d.toString();
        int indx = KDataBase::DateToIndex(d.day(), d.month(), d.year());
        updateGuiForDay(indx);
        MainWindow::openDate = d;
    }

    delete m;
}
