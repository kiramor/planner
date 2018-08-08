#include "ktask.h"
#include "kjsontools.h"

void KTask::toggleAcomplishedStatus()
{
    Acomplished = !Acomplished;
}

void KTask::writeToJson(QJsonObject &json) const
{
    json["Name"] = Name;
    json["Acomplished"] = Acomplished;
    json["Priority"] = Priority;
}

const QJsonObject KTask::writeToJson() const
{
    QJsonObject js;
    writeToJson(js);
    return js;
}

void KTask::readFromJson(const QJsonObject &json)
{
    parseJson(json, "Name", Name);
    parseJson(json, "Acomplished", Acomplished);
    parseJson(json, "Priority", Priority);
}

