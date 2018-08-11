#include "ktaskwindow.h"
#include "ui_ktaskwindow.h"

KTaskWindow::KTaskWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KTaskWindow)
{
    ui->setupUi(this);
}

KTaskWindow::~KTaskWindow()
{
    delete ui;
}
