#ifndef KTASK_H
#define KTASK_H

#include <QString>
#include <QJsonObject>
#include <QDebug>

class KTask
{
public:
    KTask() {}
    KTask(QString Name, bool Acomplished, int Priority);
    KTask(QString Name,QString AdditionalInfo, bool Acomplished, int Priority);

    QString Name = "NoName";
    QString AdditionalInfo = "No info";
    bool    Acomplished = false;
    int     Priority = 0; // 0-normal, >0 high priority, <0 lower priority

    void toggleAcomplishedStatus();

public:
    void              writeToJson(QJsonObject& json) const;
    const QJsonObject writeToJson() const;
    void              readFromJson(const QJsonObject& json);
    void print();
};

#endif // KTASK_H
