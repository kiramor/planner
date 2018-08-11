#include "kdatabase.h"
#include "kjsontools.h"

#include <QDate>
#include <QDebug>

KDataBase::KDataBase()
{
    clearBase();
}

void KDataBase::clearBase()
{
    for (KDay* day : Days) delete day;

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

    int day, month, year;
    IndexToDate(index, day, month, year);
    Days[index] = new KDay(index, day, month, year);

    //temp!
    /*
    KTask home;
    home.Name = "Homework 1";
    Days[index]->addToList(home, Days[index]->getListHomework());
    home.Priority = 4;
    home.Acomplished = false;
    home.Name = "Homework 2";
    Days[index]->addToList(home, Days[index]->getListHomework());
    home.Acomplished = false;
    home.Name = "Homework 3";
    Days[index]->addToList(home, Days[index]->getListHomework());
    home.Acomplished = true;
    home.Priority = 5;

    KTask stud;
    stud.Name = "Study One";
    Days[index]->addToList(home, Days[index]->getListStudy());
    stud.Priority = 1;
    stud.Acomplished = true;
    stud.Name = "Study Two";
    Days[index]->addToList(home, Days[index]->getListStudy());
    stud.Acomplished = true;
    stud.Name = "Study Three";
    Days[index]->addToList(home, Days[index]->getListStudy());
    stud.Priority = -1;
    stud.Acomplished = false;
    */

    KTask nt;
    nt.Name = "Generic task # 1";    
    Days[index]->addToList(nt, Days[index]->getListToDo());
    nt.Name = "Generic task # 2";
    Days[index]->addToList(nt, Days[index]->getListToDo());
    nt.Priority = 4;
    nt.Name = "Generic task # 3";
    Days[index]->addToList(nt, Days[index]->getListToDo());
    nt.Priority = 2;
    nt.Acomplished = true;
    nt.Name = "Generic task # 4";
    Days[index]->addToList(nt, Days[index]->getListToDo());
    nt.Priority = -1;

    nt.Name = "Shout out loudlyyyy";
    nt.Acomplished = true;
    Days[index]->addToList(nt, Days[index]->getListToDo());
    nt.Name = "Shout out again";
    nt.Acomplished = false;
    nt.Priority = 6;
    Days[index]->addToList(nt, Days[index]->getListToDo());
    nt.Name = "Shout out silently";
    nt.Acomplished = false;
    nt.Priority = 2;
    Days[index]->addToList(nt, Days[index]->getListToDo());



    nt.Name = "Homework 1";
    nt.Priority = 4;
    nt.Acomplished = false;
    Days[index]->addToList(nt, Days[index]->getListHomework());

    nt.Name = "Homework 2";
    nt.Acomplished = false;
    Days[index]->addToList(nt, Days[index]->getListHomework());

    nt.Name = "Homework 3";
    nt.Acomplished = true;
    nt.Priority = 5;
    Days[index]->addToList(nt, Days[index]->getListHomework());


    nt.Name = "Study One";
    nt.Priority = 1;
    nt.Acomplished = true;
    Days[index]->addToList(nt, Days[index]->getListStudy());

    nt.Name = "Study Two";
    nt.Acomplished = true;
    Days[index]->addToList(nt, Days[index]->getListStudy());

    nt.Name = "Study Three";
    nt.Priority = -1;
    nt.Acomplished = false;
    Days[index]->addToList(nt, Days[index]->getListStudy());


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

KDay *KDataBase::getDay(int index)
{
    if (isDayExist(index))
        return Days[index];
    else
        return 0;
}

const KDay *KDataBase::getDay(QDate&d) const
{
    int index = DateToIndex(d.day(), d.month(),d.year());
    if (isDayExist(index))
        return Days[index];
    else
        return 0;
}

KDay *KDataBase::getDay(QDate &d)
{
    int index = DateToIndex(d.day(), d.month(),d.year());
    if (isDayExist(index))
        return Days[index];
    else
        return 0;
    //getDay(index)
}

void KDataBase::writeToJson(QJsonObject& json) const
{
    //Days
    QJsonArray ar;
    for (const KDay* day : Days)
        if (day)
        {
            QJsonObject js;
            day->writeToJson(js);
            ar.append(js);
        }
    json["Days"] = ar;

    //everything else
}

void KDataBase::readFromJson(const QJsonObject &json)
{
    clearBase();

    QJsonArray ar;
    parseJson(json, "Days", ar);
    for (int i=0; i<ar.size(); i++)
    {
        KDay* day = new KDay();
        const QJsonObject js = ar.at(i).toObject();
        day->readFromJson(js);

        int index = DateToIndex(day->getDay(), day->getMonth(), day->getYear());
        if (index > -1)
            Days[index] = day;
        else
            qDebug() << "Something went wrong...";
    }

}

int KDataBase::DateToIndex(int day, int month, int year)
{
    QDate thisOne(year, month, day);
    QDate startOfKira(2018, 1, 1);

    int days = startOfKira.daysTo(thisOne);
    qDebug() << days;

    return days;
}

bool KDataBase::IndexToDate(int index, int &day, int &month, int &year)
{
    if (index < 0) return false;

    QDate startOfKira(2018, 1, 1);
    QDate d = startOfKira.addDays(index);
    d.getDate(&year, &month, &day);

    return true;
}
