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

void KDataBase::printDay(QDate &dt)
{
    const int index = DateToIndex(dt);
    if (index < 0 || index > maxDaysInBase)
        qDebug() << "Bad index";
    else if ( !Days.at(index) )
        qDebug() << "Day does not exist";
    else
        Days.at(index)->print();
}

bool KDataBase::isDayExist(QDate &dt) const
{
    const int index = DateToIndex(dt);
    return isDayExist(index);
}

bool KDataBase::isDayExist(int index) const
{
    if (index < 0 || index > maxDaysInBase) return false;
    return Days.at(index);
}

bool KDataBase::createDay(int index)
{
    if (index < 0 || index > maxDaysInBase) return false;
    if (isDayExist(index)) return false;

    int day, month, year;
    IndexToDate(index, day, month, year);
    Days[index] = new KDay(index, day, month, year);
    return true;
}

const QString KDataBase::createDummyDay(QDate &dt)
{
    const int index = DateToIndex(dt);
    if (index < 0 || index > maxDaysInBase) return "Bad index";

    if ( Days.at(index) )
    {
        delete Days.at(index);
        Days[index] = 0;
    }

    int day, month, year;
    IndexToDate(index, day, month, year);
    Days[index] = new KDay(index, day, month, year);

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

KDay *KDataBase::getDay(QDate &d)
{
    const int index = DateToIndex(d.day(), d.month(),d.year());
    if ( !isDayExist(index)) createDay(index);
    return Days[index];
}

void KDataBase::writeToJson(QJsonObject& json) const
{
    //Days
    QJsonArray ar;
    for (const KDay* day : Days)
        if ( !day->isDayEmpty() )
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

int KDataBase::DateToIndex(int day, int month, int year) const
{
    QDate thisOne(year, month, day);
    QDate startOfKira(2018, 1, 1);

    int days = startOfKira.daysTo(thisOne);

    return days;
}

int KDataBase::DateToIndex(const QDate &qdate) const
{
    return DateToIndex(qdate.day(), qdate.month(), qdate.year());
}

bool KDataBase::IndexToDate(int index, int &day, int &month, int &year) const
{
    if (index < 0) return false;

    QDate startOfKira(2018, 1, 1);
    QDate d = startOfKira.addDays(index);
    d.getDate(&year, &month, &day);

    return true;
}
