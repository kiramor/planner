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

    bool isDayEmpty() const;

private:
    int  Index = -1;

    int Day = -1;
    int Month = -1;
    int Year = -1;
    QDate qDate;

    QVector<KTask> ToDo;
    QVector<KTask> Homework;
    QVector<KTask> Study;

    QVector<int>   LinkToSpecialTasks;
    QVector<int>   LinkToGradedSTs;
    QVector<int>   LinkToHabits;

public:
    int getDayOfWeek();
    int getDayOfMonth();

    const QVector<KTask>& getListToDo() const {return ToDo;}
    QVector<KTask>&       getListToDo() {return ToDo;}
    const QVector<KTask>& getListHomework() const {return Homework;}
    QVector<KTask>&       getListHomework() {return Homework;}
    const QVector<KTask>& getListStudy() const {return Study;}
    QVector<KTask>&       getListStudy() {return Study;}
    //void addToDo(const KTask& todo);
    void addToList(const KTask& todo, QVector<KTask> &list);
    //void addHome(const KTask& home);
    //void addStudy(const KTask& study);
    //void addNewTask(QVector<KTask> *container);


    void print() const;

    void static sortTasks(QVector<KTask>& container);

private:
    void updateQDate();
};

#endif // KDAY_H
