#ifndef KEVENT_H
#define KEVENT_H

#include <QtGlobal> //for qint64

class QJsonObject;

class KEvent
{
public:
    KEvent(qint64 id) : id(id) {}
    KEvent() {}

    qint64 getId() {return id;}

    void writeToJson(QJsonObject& json) const;
    void readFromJson(const QJsonObject& json);

protected:
    qint64 id; //qint64 QDateTime::toMSecsSinceEpoch() const
};

#endif // KEVENT_H
