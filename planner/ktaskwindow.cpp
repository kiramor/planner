#include "ktaskwindow.h"
#include "ui_ktaskwindow.h"
#include "kday.h"

#include <QWidget>
#include <QDebug>
#include <QIntValidator>
#include <QPlainTextEdit>
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
        ui->twTable->verticalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        //done header
        ui->twTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        //priority header
        ui->twTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
        //vertical header
        ui->twTable->verticalHeader()->setMinimumSectionSize(60);


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


            /*QTableWidgetItem* itm = new QTableWidgetItem("n/a");
            itm->setData(2, tsk.AdditionalInfo);
            itm->setText("n/a");
            //item->data(2) = "jhgfds";
            ui->twTable->setItem(row, 1, itm);*/


            //QTableWidgetItem* itm2 = new QTableWidgetItem();
            QPlainTextEdit* pte = new QPlainTextEdit();
            //pte->appendPlainText(tsk.AdditionalInfo);
            pte->appendPlainText("lkjhgfdsazxcvbnhjmklkijuhygtfredsxcvbnhjkljhgtfrdesxcvbnhjkljhgtfrdcvbnjmkmjhgtfdc");
            ui->twTable->setCellWidget(row, 1, pte);










//"Line 1 \n Line 2"
            row++;
        }
        /*QTableWidgetItem* itm2 = new QTableWidgetItem("jnhbvgfcdxsewaedrftghyujikjuy7t \n rfedswadfcvgbhnjuhygtfrdesxdcfvgbhnjuhygtfr");
        //itm2->setData(2, tsk.AdditionalInfo);
        //itm2->setText("n/a");
        ui->twTable->setItem(0, 1, itm2);*/
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
    if (column==2)
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
    int n=50;
    ui->twTable->verticalHeader()->setMaximumSectionSize(n);
    ui->twTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

    for (int i = 0; i<ui->twTable->rowCount(); i++)
    {
        ui->twTable->verticalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }



    for (int i = 0; i<ui->twTable->selectedItems().size(); i++)
    {
        int r=ui->twTable->selectedItems()[i]->row();
        ui->twTable->verticalHeader()->setSectionResizeMode(r, QHeaderView::Stretch);
    }
}
