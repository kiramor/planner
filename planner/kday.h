#ifndef KDAY_H
#define KDAY_H

#include <QVector>

#include "ktask.h"

class KDay
{
public:
    KDay();

    int  Index;

    int IndexInWeek;
    int IndexInMonth;

    QVector<KTask> ToDo;
    QVector<KTask> Homework;
    QVector<KTask> Study;

    QVector<int>   LinkToEvents;
    QVector<int>   LinkToProjects;
    QVector<int>   LinkToHabits;

};

#endif // KDAY_H
