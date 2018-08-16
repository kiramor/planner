#include "ktaskwindow.h"
#include "ui_ktaskwindow.h"
#include "kday.h"

#include <QWidget>
#include <QDebug>
#include <QIntValidator>
//#include <QList>

KTaskWindow::KTaskWindow(QVector<KTask> &container, QWidget *parent) :
    Tasks(container),
    QMainWindow(parent),
    ui(new Ui::KTaskWindow)

{
    ui->setupUi(this);
    intValidator = new QIntValidator(this);
    fillTable(Tasks);
}

KTaskWindow::~KTaskWindow()
{
    delete ui;
}

#include <QHeaderView>
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

        ui->twTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        //name header
        ui->twTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        //add.. info header

        //ui->twTable->verticalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);





        //done header
        ui->twTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        //priority header
        ui->twTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);


        int row = 0;
        for (const KTask& tsk : container)
        {
            //qDebug() <<"size of container:"<<container.size() <<row;
            QTableWidgetItem* item = new QTableWidgetItem(tsk.Name);
            //item->setTextAlignment(Qt::AlignCenter);
            ui->twTable->setItem(row, 0, item);

            item = new QTableWidgetItem();
            if (tsk.Acomplished == true)
            {
                item->setText(sDone);
                item->setBackgroundColor(Qt::darkGreen);
            }
            else
                item->setText(sNotDone);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            ui->twTable->setItem(row, 2, item);

            QLineEdit *qle = new QLineEdit (QString::number(tsk.Priority));
            qle->setMaximumWidth(50);
            qle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            qle->setAlignment(Qt::AlignCenter);
            qle->setValidator(intValidator);
            ui->twTable->setCellWidget(row, 3, qle);
            //ui->twTable->setItem(row, 2, item);
            //QLineEdit *qle = new QLineEdit (ui->twTable->item(row, 2)->text(), ui->twTable->item(row,2));


            row++;




            QTableWidgetItem* itm = new QTableWidgetItem("n/a");
            ui->twTable->setItem(0, 1, itm);
            QTableWidgetItem* itm2 = new QTableWidgetItem("n/a");
            ui->twTable->setItem(1, 1, itm2);
            QTableWidgetItem* itm3 = new QTableWidgetItem("n/a");
            ui->twTable->setItem(2, 1, itm3);
            /*int max = 50;
            //item->
            ui->twTable->setRowHeight(1, max);*/
        }
}

void KTaskWindow::on_pbAccept_clicked()
{
    Tasks.clear();

    for (int i=0; i<ui->twTable->rowCount(); i++)
    {
        const QString name(ui->twTable->item(i, 0)->text());
        const bool done(ui->twTable->item(i, 2)->text() == "Done");


        QWidget* w = ui->twTable->cellWidget(i, 3);
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
        qDebug() <<"d, n, p:" <<done <<name <<priority;

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

void KTaskWindow::on_twTable_customContextMenuRequested(const QPoint &pos)
{

    /*QDialog* m = new QDialog(this);
    //m->setWindowTitle("Select date");
    QLineEdit* labAddInfo = new QLineEdit(m);
    //labAddInfo->setEnabled(fals);
    //QObject::connect(labAddInfo, &QLineEdit::returnPressed, labAddInfo, &QLineEdit::setDisabled);



    //int r = row
    int r(ui->twTable->itemAt(pos)->row());
    QString str(Tasks[r].AdditionalInfo);
    labAddInfo->setText(str);



    m->exec();
    Tasks[r].AdditionalInfo = labAddInfo->text();*/
}

void KTaskWindow::on_twTable_itemSelectionChanged()
{
    for (int i=0; i<ui->twTable->rowCount(); i++)
    {
        ui->twTable->item(i, 1)->setText("n/a");
    }


    for (int i = 0; i<ui->twTable->selectedItems().size(); i++)
    {
        //QList <QTableWidgetItem*> list = ui->twTable->selectedItems();
        //QList <QTableWidgetItem*> list = new QList <QTableWidgetItem*>(ui->twTable->selectedItems());
        int r=ui->twTable->selectedItems()[i]->row();
        qDebug() <<"selected Item" <<ui->twTable->item(r, 1)->text();
        ui->twTable->item(r, 1)->setText(Tasks[r].AdditionalInfo);
        qDebug() <<"selected Item" <<ui->twTable->item(r, 1)->text();
        //ui->twTable->hideRow()

        ui->twTable->verticalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    }
}
