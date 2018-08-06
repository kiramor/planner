#ifndef KDATABASE_H
#define KDATABASE_H

#include <Qvector>

#include "kday.h"

class KDataBase
{
public:
    KDataBase();

    bool   AddDay(KDay* NewDay, int index);

private:
    QVector<KDay*> Days;


public:
    static int DateToIndex(int day, int month, int year);
};

#endif // KDATABASE_H
