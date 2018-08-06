#include "kday.h"

#include <QDebug>

KDay::KDay(int index) :
    Index(index)
{
    qDebug() << "Creating day with index" << index;
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
    qDebug() << "Lineked to # of events:"<<LinkToEvents.size();
    qDebug() << "Lineked to # of projucts:"<<LinkToProjects.size();
    qDebug() << "Lineked to # of hobbits:"<<LinkToHabits.size();
    qDebug() << "***************";
}
