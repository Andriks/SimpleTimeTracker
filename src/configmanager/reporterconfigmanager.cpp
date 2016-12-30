#include "reporterconfigmanager.h"

#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonParseError>

#include <QDebug>


const char* ReporterConfigManager::CONFIG_FILENAME = "./config/reporter.json";
const char* ReporterConfigManager::DEFAULT_REQUEST_KEY = "default_request";
const char* ReporterConfigManager::PRODUCTIVITY_KEY = "productivity";


bool ReporterConfigManager::isValid()
{
    // TODO: implement it
    return true;
}

void ReporterConfigManager::updateConfig()
{
    mConfig = parseFile(CONFIG_FILENAME);
}

QJsonValue ReporterConfigManager::get(const char*  key)
{
    if (isValid()) {
        return mConfig[key];
    }
}

QJsonObject ReporterConfigManager::parseFile(QString filename)
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
