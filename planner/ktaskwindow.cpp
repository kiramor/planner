#include "ktaskwindow.h"
#include "ui_ktaskwindow.h"
#include "kday.h"

#include <QWidget>
#include <QDebug>
#include <QIntValidator>

KTaskWindow::KTaskWindow(QVector<KTask> &container, QWidget *parent) :
    Tasks(container),
    QMainWindow(parent),
    ui(new Ui::KTaskWindow)

{
    ui->setupUi(this);
    intValidator = new QIntValidator(this);
    fillTable(Tasks);
    qDebug() <<"validator in constructor!!!!!!:"<<intValidator;
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

            if (tsk.Acomplished == true)
            {
                //qDebug() <<"size of container:"<<container.size() <<row;
                item = new QTableWidgetItem(sDone);
                item->setBackgroundColor(Qt::darkGreen);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->twTable->setItem(row, 1, item);
            }
            else
            {
                item = new QTableWidgetItem(sNotDone);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->twTable->setItem(row, 1, item);
            }


            QLineEdit *qle = new QLineEdit (QString::number(tsk.Priority));
            qDebug() <<"validator:"<<intValidator;
            qle->setValidator(intValidator);
            ui->twTable->setCellWidget(row, 2, qle);
            //ui->twTable->setItem(row, 2, item);
            //QLineEdit *qle = new QLineEdit (ui->twTable->item(row, 2)->text(), ui->twTable->item(row,2));


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

        QWidget* w = ui->twTable->cellWidget(i, 2);
        QLineEdit* le = dynamic_cast<QLineEdit*>(w);
        int priority = 0;
        if (le)
        {
            priority = le->text().toInt();
        }
        else
        {
            qDebug() << "line edit is null";
        }
        //const int priority(ui->twTable->item.(i, 2)->text().toInt());
        qDebug() <<"tasks3" <<priority;
        qDebug() <<"tasks4" <<done <<name <<priority;

        Tasks << KTask(name, done, priority);

    }

    emit TaskWindowClosed();
    deleteLater();
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

    }
}

void KTaskWindow::on_pbCancel_clicked()
{
    emit TaskWindowClosed();
    deleteLater();
}
