#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kdatabase.h"
#include "kjsontools.h"
#include "ktaskwindow.h"
#include "ksingletaskview.h"

#include <QDebug>

#include <QDialog>
#include <QCalendarWidget>


MainWindow::MainWindow(KDataBase &dataBase, QWidget *parent) :
    QMainWindow(parent), DataBase(dataBase), ui(new Ui::MainWindow), OpenDate(QDate::currentDate())
{
    ui->setupUi(this);

    ui->lwToDo->setDragDropMode(QAbstractItemView::DragDrop);
    ui->lwToDo->setDefaultDropAction(Qt::MoveAction);

    loadBase();
    updateGuiForOpenDay();
}

MainWindow::~MainWindow()
{
    saveBase();
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

void MainWindow::addNewTask()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    KTask tsk;
    //tsk.Name = "helllo";
    //qDebug() <<"addnewtaskclicked";

    if (ui->lwStudy->hasFocus())
    {
        thisDay->getListStudy().append(tsk);
        openKSingleView(thisDay->getListStudy().last());
        //updateGuiForOpenDay();
    }
    else if (ui->lwToDo->hasFocus())
    {
        thisDay->getListToDo().append(tsk);
        openKSingleView(thisDay->getListToDo().last());
    }
    else if (ui->lwHome->hasFocus())
    {
        thisDay->getListHomework().append(tsk);
        openKSingleView(thisDay->getListHomework().last());
    }


}

void MainWindow::createActions()
{
    /*QAction*newAct = new QAction(tr("&New"), this);
    //newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new Task"));
    connect(newAct, &QAction::triggered, this, &MainWindow::addNewTask);*/

}

void MainWindow::createMenu()
{

}

void MainWindow::openKSingleView_ToDo()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    int cr =ui->lwToDo->currentRow();
    KTask& tsk = (thisDay->getListToDo()[cr]);
    openKSingleView(tsk);
}

void MainWindow::openKSingleView_Study()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    int cr =ui->lwStudy->currentRow();
    KTask& tsk = (thisDay->getListStudy()[cr]);
    openKSingleView(tsk);
}

void MainWindow::openKSingleView_Home()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    int cr =ui->lwHome->currentRow();
    KTask& tsk = (thisDay->getListHomework()[cr]);
    openKSingleView(tsk);
}

void MainWindow::openKSingleView(KTask &tsk)
{
    KSingleTaskView* stw = new KSingleTaskView(tsk, this);
    stw->setWindowModality(Qt::WindowModal);
    QObject::connect(stw, &KSingleTaskView::STaskViewClosed, this, &MainWindow::updateGuiForOpenDay);
    //QObject::connect(stw, &KSingleTaskView::STaskViewClosed, this, &MainWindow::tempfun);
    KDay* thisDay = DataBase.getDay(OpenDate);

    for (KTask&tsk:thisDay->getListStudy())
    {
        tsk.print();
    }

    stw->show();
    qDebug() <<"stw->show()\n-----------------------";

    /*for (KTask&tsk:thisDay->getListStudy())
    {
        tsk.print();
    }*/
    //
}




#include <QMenu>
void MainWindow::on_lwToDo_customContextMenuRequested(const QPoint &pos)
{
    QVector<KTask> &container = DataBase.getDay(OpenDate)->getListToDo();
    customContextMenuForWidget(pos, ui->lwToDo, container);

}

void MainWindow::customContextMenuForWidget(const QPoint &pos, QListWidget *widget, QVector<KTask> &container)
{
    QMenu m;
    int row = -1;

    //QString shownItemType;
    QListWidgetItem* temp = widget->itemAt(pos);

    QAction* toggleDone = 0;
    QAction* deleteTask = 0;

    if (temp)
      {
        //menu triggered at a valid item
        row = widget->row(temp);

        m.addSeparator();
        toggleDone = m.addAction("Change done state");

        m.addSeparator();
        deleteTask = m.addAction("Delete task");

      }

    m.addSeparator();
    QAction* newTask = m.addAction("Create new task");
    //
    QAction* selectedItem = m.exec(widget->mapToGlobal(pos));

    if (!selectedItem)//nothing was selected
    {
        qDebug() <<"nothing selected";
        return;
    }

    if (selectedItem == toggleDone)
    {
        int currentTask = row;
        if (DataBase.isDayExist(OpenDate))
        {
            //KDay* thisDay = DataBase.getDay(OpenDate);
            if (currentTask < container.size())
                //qDebug() <<"huh wanna toggle?";
                container[currentTask].toggleAcomplishedStatus();
            updateGuiForOpenDay();
        }

    }

    else if (selectedItem == newTask)
    {
        qDebug() <<"selected item= new task";
        if (DataBase.isDayExist(OpenDate))
        {
            addNewTask();
            //updateGuiForOpenDay();
        }
    }
    else if (selectedItem == deleteTask)
    {
        qDebug() <<"selected item= delete Task";
        if (DataBase.isDayExist(OpenDate))
        {
            container.remove(row);
            updateGuiForOpenDay();
        }
    }

    else
    {
        qDebug() << "!!!!!----------  OpenDay does not exist";
    }
}

void MainWindow::tempfun()
{
    KDay* thisDay = DataBase.getDay(OpenDate);
    for (KTask&tsk:thisDay->getListStudy())
    {
        tsk.print();
    }
}


void MainWindow::on_actionSave_triggered()
{
    saveBase();
}

void MainWindow::on_actionLoad_triggered()
{
    loadBase();
    updateGuiForOpenDay();
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


void MainWindow::on_lwStudy_itemDoubleClicked(QListWidgetItem *item)
{
    /*qDebug() <<"you double clicked!!";
    KDay* thisDay = DataBase.getDay(OpenDate);
    int cr =ui->lwStudy->currentRow();
    KTask& tsk = (thisDay->getListStudy()[cr]);
    KSingleTaskView* stw = new KSingleTaskView(tsk, this);
    QObject::connect(stw, &KSingleTaskView::STaskViewClosed, this, &MainWindow::updateGuiForOpenDay);


    stw->show();*/
    openKSingleView_Study();
}

void MainWindow::on_lwStudy_itemClicked(QListWidgetItem *item)
{
    /*KSingleTaskView* stw = new KSingleTaskView(this);
    qDebug() <<"you clicked!!";

    //stw->setWindowModality(Qt::WindowModal);
    //QObject::connect(stw, &KSpecialTaskView::TaskWindowClosed, this, &MainWindow::updateGuiForOpenDay);
    stw->show();*/
}

void MainWindow::on_lwToDo_itemDoubleClicked(QListWidgetItem *item)
{
    /*qDebug() <<"you double clicked!!";
    KDay* thisDay = DataBase.getDay(OpenDate);
    int cr =ui->lwToDo->currentRow();
    KTask& tsk = (thisDay->getListToDo()[cr]);
    KSingleTaskView* stw = new KSingleTaskView(tsk, this);
    QObject::connect(stw, &KSingleTaskView::STaskViewClosed, this, &MainWindow::updateGuiForOpenDay);


    stw->show();*/
    openKSingleView_ToDo();
}

void MainWindow::on_lwHome_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() <<"you double clicked!!";
    /*KDay* thisDay = DataBase.getDay(OpenDate);
    int cr =ui->lwHome->currentRow();
    KTask& tsk = (thisDay->getListHomework()[cr]);
    KSingleTaskView* stw = new KSingleTaskView(tsk, this);
    QObject::connect(stw, &KSingleTaskView::STaskViewClosed, this, &MainWindow::updateGuiForOpenDay);


    stw->show();*/
    openKSingleView_Home();
}

void MainWindow::on_lwStudy_customContextMenuRequested(const QPoint &pos)
{
    QVector<KTask> &container = DataBase.getDay(OpenDate)->getListStudy();
    customContextMenuForWidget(pos, ui->lwStudy, container);
}

void MainWindow::on_lwHome_customContextMenuRequested(const QPoint &pos)
{
    QVector<KTask> &container = DataBase.getDay(OpenDate)->getListHomework();
    customContextMenuForWidget(pos, ui->lwHome, container);
}
