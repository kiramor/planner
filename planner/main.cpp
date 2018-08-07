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

    int day, month, year;
    KDataBase::IndexToDate(31477, day, month, year);
    qDebug() << day << month << year;

    return a.exec();
}
