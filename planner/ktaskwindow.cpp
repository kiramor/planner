#include "ktaskwindow.h"
#include "ui_ktaskwindow.h"
#include "kday.h"

#include <QWidget>
#include <QDebug>
KTaskWindow::KTaskWindow(QVector<KTask> &container, QWidget *parent) :
    Tasks(container),
    QMainWindow(parent),
    ui(new Ui::KTaskWindow)
{
    ui->setupUi(this);
    fillTable(Tasks);
}

KTaskWindow::~KTaskWindow()
{
    delete ui;
}

void KTaskWindow::fillTable(QVector<KTask> &container)
{
    if (true)//container.size() >0)
    {
        //ui->twTable->insertRow(0);
        //ui->twTable->setItem(0, 0, new QTableWidgetItem("Hello"));
        KDay::sortTasks(container);


        //qDebug() <<"size of container:"<<container.size();

        for (int i=0; i<container.size(); i++)
        {
            ui->twTable->insertRow(i);
        }

        int row=0;
        for (const KTask& tsk : container)
        {
            //qDebug() <<"size of container:"<<container.size() <<row;
            QTableWidgetItem* item =new QTableWidgetItem(tsk.Name);
            ui->twTable->setItem(row, 0, item);
            row++;

        }

        row=0;
        for (const KTask& tsk : container)
        {
            if (tsk.Acomplished== true)
            {
                //qDebug() <<"size of container:"<<container.size() <<row;
                QTableWidgetItem* item =new QTableWidgetItem("Done");
                ui->twTable->setItem(row, 1, item);
                item->setBackgroundColor(Qt::darkGreen);
            }
            else
            {
                QTableWidgetItem* item =new QTableWidgetItem("Not Done");
                ui->twTable->setItem(row, 1, item);
            }
            row++;
        }
        row=0;
        for (const KTask& tsk : container)
        {
            qDebug() <<"size of container:"<<container.size() <<row <<tsk.Priority;
            QTableWidgetItem* item =new QTableWidgetItem(QString::number(tsk.Priority));
            ui->twTable->setItem(row, 2, item);
            row++;
        }

            /*QTableWidgetItem *item = new QTableWidgetItem(todo.Name);
            if (todo.Acomplished) item->setBackgroundColor(Qt::darkGreen);
            //twTable.addItem(item);
            ui->twTable->editItem(item);

            int row=0;
            int col=0;
            //ui->twTable->setCellWidget(row++, col++, ui->twTable);
            ui->twTable->setItem(0, 1, new QTableWidgetItem("Hello"));*/


    }
}
