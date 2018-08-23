#ifndef KDATABASE_H
#define KDATABASE_H

#include <Qvector>
#include <QMap>

#include "kday.h"

class KEvent;

class KDataBase
{
public:
    KDataBase();

    void printDay(QDate &dt); //temporary
    bool isDayExist(QDate &dt) const;
    const QString createDummyDay(QDate &dt); //return "" if seccess

    KDay* getDay(QDate &d);

    void writeToJson(QJsonObject &json) const;
    void readFromJson(const QJsonObject &json);

private:
    const int maxDaysInBase = 36500;
    QVector<KDay*> Days;

    QMap<qint64, KEvent*> Events;

    bool isDayExist(int index) const;
    bool createDay(int index);
    void clearBase();

    int  DateToIndex(int day, int month, int year) const;
    int  DateToIndex(const QDate& qdate) const;
    bool IndexToDate(int index, int& day, int& month, int& year) const;

};

#endif // KDATABASE_H
