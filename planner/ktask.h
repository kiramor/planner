#ifndef KTASK_H
#define KTASK_H

#include <QString>

class KTask
{
public:
    KTask();

    QString Name = "NoName";
    bool    Status = false;
    int     Priority = 0; // 0-normal, >0 high priority, <0 lower priority
    QString AfterComment;
};

#endif // KTASK_H
