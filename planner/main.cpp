#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <kdatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    KDataBase dataBase;
    MainWindow w(dataBase);
    w.show();

    qDebug() << KDataBase::DateToIndex(7, 3, 2104);

    return a.exec();
}
