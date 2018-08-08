#ifndef KDAY_H
#define KDAY_H

#include <QVector>
#include <QDate>

#include "ktask.h"

class QJsonObject;

class KDay
{
public:
    KDay(int index, int day, int month, int year);
    KDay(){}

    void writeToJson(QJsonObject &json) const;
    void readFromJson(const QJsonObject &json);

    int getDay() const {return Day;}
    int getMonth() const {return Month;}
    int getYear() const {return Year;}
    const QDate& getQDate() const {return qDate;}

private:
    int  Index = -1;

    int Day = -1;
    int Month = -1;
    int Year = -1;
    QDate qDate;

    QVector<KTask> ToDo;
    QVector<KTask> Homework;
    QVector<KTask> Study;

    //QVector<int>   LinkToEvents;
    //QVector<int>   LinkToProjects;
    QVector<int>   LinkToSpecialTasks;
    QVector<int>   LinkToGradedST;
    QVector<int>   LinkToHabits;

public:
    int getDayOfWeek();
    int getDayOfMonth();

    const QVector<KTask>& getListToDo() const {return ToDo;}
    QVector<KTask>&       getListToDo() {return ToDo;}
    void addToDo(const KTask& todo);

    void print() const;

    void static sortTasks(QVector<KTask>& container);

private:
    void updateQDate();
};

#endif // KDAY_H
