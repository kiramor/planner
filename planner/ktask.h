#ifndef KTASK_H
#define KTASK_H

#include <QString>
#include <QJsonObject>
#include <QDebug>

class KTask
{
public:
    KTask() {}

    QString Name = "NoName";
    bool    Acomplished = false;
    int     Priority = 0; // 0-normal, >0 high priority, <0 lower priority

    void toggleAcomplishedStatus();

public:
    void              writeToJson(QJsonObject& json) const;
    const QJsonObject writeToJson() const;
    void              readFromJson(const QJsonObject& json);
};

#endif // KTASK_H
