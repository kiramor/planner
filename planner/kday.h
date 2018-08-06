#ifndef KDAY_H
#define KDAY_H

#include <QVector>
#include <QDate>

#include "ktask.h"

class KDay
{
public:
    KDay(int index);
    KDay(){}


    QVector<KTask> Homework;
    QVector<KTask> Study;

    QVector<int>   LinkToEvents;
    QVector<int>   LinkToProjects;
    QVector<int>   LinkToHabits;

private:
    int  Index = -1;

    QVector<KTask> ToDo;

public:
    int getDayOfWeek();
    int getDayOfMonth();

    const QVector<KTask> getListToDo() const {return ToDo;}
    void addToDo(const KTask& todo);

    void print() const;

};

#endif // KDAY_H
