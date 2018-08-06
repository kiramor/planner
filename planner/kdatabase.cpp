#include "kdatabase.h"

#include <QDate>
#include <QDebug>

KDataBase::KDataBase()
{
    Days = QVector<KDay*>(36500, 0);
}

bool KDataBase::AddDay(KDay *NewDay, int index)
{
    if (Days.at(index)) return false;

    Days[index] = NewDay;
}

int KDataBase::DateToIndex(int day, int month, int year)
{
    QDate mama(year, month, day);
    QDate kira(2004, 3, 7);

    int days = kira.daysTo(mama);
    qDebug() << days;

    return days;
}
