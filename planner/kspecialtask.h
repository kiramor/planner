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
    QVector<QVector<int>> LinktoTasks;//(?) I want to have several lists of preparations
    QString AfterComment;

};

#endif // KSPECIALTASK_H
