#include "kjsontools.h"

#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>

#include <QJsonDocument>
#include <QDebug>
#include <QFile>

bool parseJson(const QJsonObject &json, const QString &key, bool &var)
{
  if (json.contains(key))
    {
      var = json[key].toBool();
      return true;
    }
  else return false;
}

bool parseJson(const QJsonObject &json, const QString &key, int &var)
{
  if (json.contains(key))
    {
      //var = json[key].toInt();
      double val = json[key].toDouble();
      var = std::round(val);
      return true;
    }
  else return false;
}

bool parseJson(const QJsonObject &json, const QString &key, double &var)
{
  if (json.contains(key))
    {
      var = json[key].toDouble();
      return true;
    }
  else return false;
}

bool parseJson(const QJsonObject &json, const QString &key, float &var)
{
  if (json.contains(key))
    {
      var = json[key].toDouble();
      return true;
    }
  else return false;
}

bool parseJson(const QJsonObject &json, const QString &key, QString &var)
{
  if (json.contains(key))
    {
      var = json[key].toString();
      return true;
    }
  else return false;
}

bool parseJson(const QJsonObject &json, const QString &key, QJsonArray &var)
{
  if (json.contains(key))
    {
      var = json[key].toArray();
      return true;
    }
  else return false;
}

bool parseJson(const QJsonObject &json, const QString &key, QJsonObject &obj)
{
    if (json.contains(key))
      {
        obj = json[key].toObject();
        return true;
      }
    else return false;
}

void JsonToCheckbox(QJsonObject &json, QString key, QCheckBox *cb)
{
  if (json.contains(key))
    cb->setChecked(json[key].toBool());
}

void JsonToSpinBox(QJsonObject &json, QString key, QSpinBox *sb)
{
  if (json.contains(key))
    {
       double val = json[key].toDouble();
       int ival = std::round(val);
       sb->setValue(ival);
    }
}

void JsonToLineEditDouble(QJsonObject &json, QString key, QLineEdit *le)
{
  if (json.contains(key))
    le->setText( QString::number(json[key].toDouble()) );
}

void JsonToLineEditInt(QJsonObject &json, QString key, QLineEdit *le)
{
    if (json.contains(key))
        le->setText( QString::number(json[key].toInt()) );
}

void JsonToLineEditText(QJsonObject &json, QString key, QLineEdit *le)
{
    if (json.contains(key))
      le->setText( json[key].toString() );
}

void JsonToComboBox(QJsonObject &json, QString key, QComboBox *qb)
{
  if (json.contains(key))
    {
      int index = json[key].toInt();
      if (index >= qb->count()) index = -1;
      qb->setCurrentIndex(index);
    }
}

bool LoadJsonFromFile(QJsonObject &json, QString fileName)
{
    QFile loadFile(fileName);
    if (loadFile.open(QIODevice::ReadOnly))
      {
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        json = loadDoc.object();
        loadFile.close();
        //  qDebug()<<"  Loaded Json from file:"<<fileName;
        return true;
      }
    else
      {
        //  qDebug() << "Cannot open file:" << fileName;
        return false;
      }
}

bool SaveJsonToFile(QJsonObject &json, QString fileName)
{
  QJsonDocument saveDoc(json);

  QFile saveFile(fileName);
  if (saveFile.open(QIODevice::WriteOnly))
    {
      saveFile.write(saveDoc.toJson());
      saveFile.close();
      //  qDebug()<<"  Saved Json to file:"<<fileName;
      return true;
    }
  else
    {
      //  qDebug() << "Couldn't save json to file: "<<fileName;
      return false;
    }
}

bool isContainAllKeys(QJsonObject json, QStringList keys)
{
    for (QString key : keys)
        if (!json.contains(key)) return false;
    return true;
}

const QJsonObject strToObject(const QString &s)
{
    QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8());
    return doc.object();
}

const QString jsonToString(const QJsonObject &json)
{
    QJsonDocument doc(json);
    QString s( doc.toJson(QJsonDocument::Compact) );
    return s;
}

