#include "jsonparser.h"

#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonParseError>

#include <QDebug>

QJsonObject JsonParser::read(const QString filename)
{
    QFile jsonFile(filename);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "TODO: add error handing - " << "Can't open file " << filename;
        qDebug() << "hint - absolute path " << QFileInfo(jsonFile).absoluteFilePath();
        return QJsonObject();
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonFile.readAll(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        jsonFile.close();
        qDebug() << "TODO: add error handing - " << "Problems with file parsing " << filename;
        return QJsonObject();
    }

    if (jsonDoc.isEmpty()) {
        jsonFile.close();
        qDebug() << "TODO: add error handing - " << "JsonDocument of file " << filename << " is empty";
        return QJsonObject();
    }

    jsonFile.close();

    return jsonDoc.object();
}
