#include "kday.h"
#include "kjsontools.h"

#include <QDebug>

KDay::KDay(int index, int day, int month, int year) :
    Index(index), Day(day), Month(month), Year(year)
{
    qDebug() << "Creating day with index" << index;
}

void KDay::writeToJson(QJsonObject &json) const
{
    json["Index"] = Index;

    json["Date_day"] = Day;
    json["Date_month"] = Month;
    json["Date_year"] = Year;

    //tasks

    //...
}

int KDay::getDayOfWeek()
{
    return 0;
}

int KDay::getDayOfMonth()
{
    return 0;
}

void KDay::addToDo(const KTask &todo)
{
    ToDo.append(todo);
}

void KDay::print() const
{
    qDebug() << "***************";
    qDebug() << " Day with index"<<Index;
    qDebug() << "Number of ToDos:"<<ToDo.size();
    qDebug() << "Number of Homeworks:"<<Homework.size();
    qDebug() << "Number of Studies:"<<Study.size();
    qDebug() << "-----------------";
    qDebug() << "Lineked to # of SpecialTasks:"<<LinkToSpecialTasks.size();
    qDebug() << "Lineked to # of GradedST:"<<LinkToGradedST.size();
    qDebug() << "Lineked to # of hobbits:"<<LinkToHabits.size();
    qDebug() << "***************";
}
