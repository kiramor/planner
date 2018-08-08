#ifndef KDATABASE_H
#define KDATABASE_H

#include <Qvector>

#include "kday.h"

class KDataBase
{
public:
    KDataBase();

    void printDay(int index);

    bool          isDayExist(int index) const;
    const QString createDay(int index); //return "" if seccess

    const KDay*   getDay(int index) const;
    KDay*         getDay(int index);

    void writeToJson(QJsonObject &json) const;
    void readFromJson(const QJsonObject &json);

private:
    const int maxDaysInBase = 36500;
    QVector<KDay*> Days;

    void clearBase();
public:
    static int  DateToIndex(int day, int month, int year);
    static bool IndexToDate(int index, int& day, int& month, int& year);
};

#endif // KDATABASE_H
