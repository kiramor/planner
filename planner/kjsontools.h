#ifndef KJSONTOOLS_H
#define KJSONTOOLS_H

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

class QCheckBox;
class QSpinBox;
class QLineEdit;
class QComboBox;

bool parseJson(const QJsonObject &json, const QString &key, bool &var);
bool parseJson(const QJsonObject &json, const QString &key, int &var);   //can convert double content of the key to int - uses std::round
bool parseJson(const QJsonObject &json, const QString &key, double &var);
bool parseJson(const QJsonObject &json, const QString &key, float &var);
bool parseJson(const QJsonObject &json, const QString &key, QString &var);
bool parseJson(const QJsonObject &json, const QString &key, QJsonArray &var);
bool parseJson(const QJsonObject &json, const QString &key, QJsonObject &obj);
bool parseJson(const QJsonObject &json, const QString &key, qint64 &var);

void JsonToCheckbox(QJsonObject& json, QString key, QCheckBox* cb);
void JsonToSpinBox(QJsonObject& json, QString key, QSpinBox* sb);
void JsonToLineEditDouble(QJsonObject& json, QString key, QLineEdit* le);
void JsonToLineEditInt(QJsonObject& json, QString key, QLineEdit* le);
void JsonToLineEditText(QJsonObject& json, QString key, QLineEdit* le);
void JsonToComboBox(QJsonObject& json, QString key, QComboBox* qb);

bool LoadJsonFromFile(QJsonObject &json, QString fileName);
bool SaveJsonToFile(QJsonObject &json, QString fileName);

bool isContainAllKeys(QJsonObject json, QStringList keys);

const QJsonObject strToObject(const QString& s);
const QString jsonToString(const QJsonObject& json);

#endif // KJSONTOOLS_H
