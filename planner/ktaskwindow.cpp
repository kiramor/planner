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
    ui->twTable->clear();
    if (container.isEmpty()) return;

        //ui->twTable->insertRow(0);
        //ui->twTable->setItem(0, 0, new QTableWidgetItem("Hello"));
        KDay::sortTasks(container);

        //qDebug() <<"size of container:"<<container.size();

        for (int i=0; i<container.size(); i++)
            ui->twTable->insertRow(i);

        int row = 0;
        for (const KTask& tsk : container)
        {
            //qDebug() <<"size of container:"<<container.size() <<row;
            QTableWidgetItem* item = new QTableWidgetItem(tsk.Name);
            ui->twTable->setItem(row, 0, item);

            if (tsk.Acomplished == true)
            {
                //qDebug() <<"size of container:"<<container.size() <<row;
                item = new QTableWidgetItem("Done");
                item->setBackgroundColor(Qt::darkGreen);
                ui->twTable->setItem(row, 1, item);
            }
            else
            {
                item = new QTableWidgetItem("Not Done");
                ui->twTable->setItem(row, 1, item);
            }

            qDebug() <<"size of container:"<<container.size() <<row <<tsk.Priority;
            item = new QTableWidgetItem(QString::number(tsk.Priority));
            ui->twTable->setItem(row, 2, item);

            row++;
        }
}
