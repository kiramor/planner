#include "ktask.h"
#include "kjsontools.h"

KTask::KTask(QString Name, bool Acomplished, int Priority):
    Name(Name), Acomplished(Acomplished), Priority(Priority)
{

}

void KTask::toggleAcomplishedStatus()
{
    Acomplished = !Acomplished;
    //qDebug() <<"toggled!!";
}

void KTask::writeToJson(QJsonObject &json) const
{
    json["Name"] = Name;
    json["Acomplished"] = Acomplished;
    json["Priority"] = Priority;
    json["AdditionalInfo"] = AdditionalInfo;
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
    parseJson(json, "AdditionalInfo", AdditionalInfo);
}

