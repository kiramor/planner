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
    ui->twTable->clearContents();
    //ui->twTable->removeRow())

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
            //item->setFlags(item->flags() ^ Qt::ItemIsEditable);

            if (tsk.Acomplished == true)
            {
                //qDebug() <<"size of container:"<<container.size() <<row;
                item = new QTableWidgetItem(sDone);
                item->setBackgroundColor(Qt::darkGreen);
                ui->twTable->setItem(row, 1, item);
            }
            else
            {
                item = new QTableWidgetItem(sNotDone);
                ui->twTable->setItem(row, 1, item);
            }

            qDebug() <<"size of container:"<<container.size() <<row <<tsk.Priority;
            item = new QTableWidgetItem(QString::number(tsk.Priority));
            ui->twTable->setItem(row, 2, item);
            //item->setFlags(item->flags() ^ Qt::ItemIsEditable);

            row++;
        }
}

void KTaskWindow::on_pbAccept_clicked()
{
    qDebug() <<"Ja tugvfdfsgthyjndbvgshynj" <<ui->twTable->rowCount();
    Tasks.clear();
    qDebug() <<Tasks.size();

    for (int i=0; i<ui->twTable->rowCount(); i++)
    {
        qDebug() <<i;
        const QString name(ui->twTable->item(i, 0)->text());
        qDebug() <<"tasks1" <<name;
        const bool done(ui->twTable->item(i, 1)->text() == "Done");
        const int priority(ui->twTable->item(i, 2)->text().toInt());
        qDebug() <<"tasks3" <<priority;
        qDebug() <<"tasks4" <<done <<name <<priority;
        Tasks << KTask(name, done, priority);
        //qDebug() <<Tasks[i].Name;

    }

    emit TaskWindowClosed();
    //deleteLater();
}

void KTaskWindow::on_twTable_cellDoubleClicked(int row, int column)
{
    if (column==1)
    {
        if (ui->twTable->item(row, column)->text() == sDone)
        {
            ui->twTable->item(row, column)->setText(sNotDone);
        }

        else if (ui->twTable->item(row, column)->text() == sNotDone)
        {
            ui->twTable->item(row, column)->setText(sDone);
        }
    //fillTable(Tasks);
    }
}

void KTaskWindow::on_pbCancel_clicked()
{
    emit TaskWindowClosed();
    deleteLater();
}
