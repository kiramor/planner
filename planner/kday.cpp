#include "kday.h"
#include "kjsontools.h"

#include <QDebug>

KDay::KDay(int index, int day, int month, int year) :
    Index(index), Day(day), Month(month), Year(year)
{
    updateQDate();
}

void KDay::writeToJson(QJsonObject &json) const
{
    json["Index"] = Index;

    json["Date_day"] = Day;
    json["Date_month"] = Month;
    json["Date_year"] = Year;

    //tasks
    QJsonArray ar;
    for (const KTask& task : ToDo)
        ar << task.writeToJson();
    json["ToDo"] = ar;
}

void KDay::readFromJson(const QJsonObject &json)
{
    parseJson(json, "Index", Index);

    parseJson(json, "Date_day", Day);
    parseJson(json, "Date_month", Month);
    parseJson(json, "Date_year", Year);
    updateQDate();

    ToDo.clear();
    QJsonArray ar;
    parseJson(json, "ToDo", ar);
    for (int i=0; i<ar.size(); i++)
    {
        QJsonObject js = ar.at(i).toObject();
        KTask task;
        task.readFromJson(js);
        ToDo << task;

    }
}

bool KDay::isDayEmpty() const
{
    if (!ToDo.isEmpty()) return false;
    if (!Homework.isEmpty()) return false;
    if (!Study.isEmpty()) return false;

    if (!LinkToSpecialTasks.isEmpty()) return false;
    if (!LinkToGradedSTs.isEmpty()) return false;
    if (!LinkToHabits.isEmpty()) return false;

    return true;
}

int KDay::getDayOfWeek()
{
    return 0;
}

int KDay::getDayOfMonth()
{
    return 0;
}
/*
void KDay::addToDo(const KTask &todo)
{
    ToDo.append(todo);
}
*/
void KDay::addToList(const KTask &todo, QVector<KTask> &list)
{
    list.append(todo);
}
/*
void KDay::addHome(const KTask &home)
{
    Homework.append(home);
}

void KDay::addStudy(const KTask &study)
{
    Study.append(study);
}
*/
void KDay::print() const
{
    qDebug() << "***************";
    qDebug() << " Day with index"<<Index;
    qDebug() << "Number of ToDos:"<<ToDo.size();
    qDebug() << "Number of Homeworks:"<<Homework.size();
    qDebug() << "Number of Studies:"<<Study.size();
    qDebug() << "-----------------";

    qDebug() << "Lineked to # of special tasks:"<<LinkToSpecialTasks.size();
    qDebug() << "Lineked to # of graded especial tasks:"<<LinkToGradedSTs.size();
    qDebug() << "Lineked to # of hobbits:"<<LinkToHabits.size();
    qDebug() << "***************";
}

void KDay::sortTasks(QVector<KTask> & container)
{
    std::sort(container.begin(), container.end(),
              []( const KTask& lhs, const KTask& rhs )
    {
        if (lhs.Acomplished && !rhs.Acomplished) return false;
        if (!lhs.Acomplished && rhs.Acomplished) return true;
        return lhs.Priority > rhs.Priority;
    }
    );

}

void KDay::updateQDate()
{
    qDate = QDate(Year, Month, Day);
}
