#include "kdatabase.h"

#include <QDate>
#include <QDebug>

KDataBase::KDataBase()
{
    Days = QVector<KDay*>(maxDaysInBase, 0);
}

void KDataBase::printDay(int index)
{
    if (index < 0 || index > maxDaysInBase)
        qDebug() << "Bad index";
    else if ( !Days.at(index) )
        qDebug() << "Day does not exist";
    else
        Days.at(index)->print();
}

bool KDataBase::isDayExist(int index) const
{
    if (index < 0 || index > maxDaysInBase) return false;
    return Days.at(index);
}

const QString KDataBase::createDay(int index)
{
    if (index < 0 || index > maxDaysInBase) return "Bad index";
    if ( Days.at(index) ) return "Already exists";

    Days[index] = new KDay(index);

    //temp!
    KTask nt;
    nt.Name = "Generic task # 1";
    Days[index]->addToDo(nt);
    nt.Name = "Shout out loudlyyyy";
    Days[index]->addToDo(nt);

    //temp!

    return "";
}

const KDay *KDataBase::getDay(int index) const
{
    if (isDayExist(index))
        return Days.at(index);
    else
        return 0;
}

int KDataBase::DateToIndex(int day, int month, int year)
{
    QDate mama(year, month, day);
    QDate kira(2004, 3, 7);

    int days = kira.daysTo(mama);
    qDebug() << days;

    return days;
}
