#ifndef KSPECIALTASK_H
#define KSPECIALTASK_H

#include "ktask.h"

#include <QString>
#include <QVector>

class KSpecialTask : public KTask
{
public:
    KSpecialTask();

    int          StartDay;
    int          EndDay;
    QVector<int> LinktoTasks;

};

#endif // KSPECIALTASK_H
