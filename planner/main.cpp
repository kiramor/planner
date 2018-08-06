#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <kdatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug() << KDataBase::DateToIndex(6, 8, 2018);

    return a.exec();
}
