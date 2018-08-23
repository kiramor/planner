#include "kevent.h"
#include "kjsontools.h"

void KEvent::writeToJson(QJsonObject &json) const
{
    json["id"] = id;

    //everything else
}

void KEvent::readFromJson(const QJsonObject &json)
{
    parseJson(json, "id", id);

    //everything else
}
