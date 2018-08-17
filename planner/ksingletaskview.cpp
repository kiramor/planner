#include "ksingletaskview.h"
#include "ui_ksingletaskview.h"

KSingleTaskView::KSingleTaskView(KTask &tsk, QWidget *parent) :
    QMainWindow(parent), Task(tsk),
    ui(new Ui::KSingleTaskView)
{
    ui->setupUi(this);
    fillWindow();
}

KSingleTaskView::~KSingleTaskView()
{
    delete ui;
}

void KSingleTaskView::fillWindow()
{
    ui->leName->setText(Task.Name);
    ui->pteAInfo->appendPlainText(Task.AdditionalInfo);
    bool done = (Task.Acomplished);
    if(done) ui->cbDone->setCheckState(Qt::Checked);
    else ui->cbDone->setCheckState(Qt::Unchecked);
    ui->sbPriority->setValue(Task.Priority);
}



void KSingleTaskView::on_pbAccept_clicked()
{
    QString name = (ui->leName->text());
    //qDebug() <<ui->pteAInfo->toPlainText();
    QString AInfo = (ui->pteAInfo->toPlainText());
    bool done;
    if (ui->cbDone->checkState()== Qt::Checked) done=true;
    else if(ui->cbDone->checkState() == Qt::Unchecked) done=false;
    //else done=false
    int priority = ui->sbPriority->value();

    Task.Name = name;
    Task.AdditionalInfo = AInfo;
    Task.Acomplished = done;
    Task.Priority = priority;

    emit STaskViewClosed();
    deleteLater();
}
