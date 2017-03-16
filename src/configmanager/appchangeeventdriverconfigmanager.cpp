#include "appchangeeventdriverconfigmanager.h"
#include "jsonparser.h"

#include <QDebug>

const char* AppChangeEventDriverConfigManager::CONFIG_FILENAME = "./config/appchangeeventdriver.json";
const char* AppChangeEventDriverConfigManager::REPORT_FROM_KEY = "report_from";
const char* AppChangeEventDriverConfigManager::REPORT_TILL_KEY = "report_till";

bool AppChangeEventDriverConfigManager::isValid()
{
    // TODO: implement it
    return true;
}

void AppChangeEventDriverConfigManager::updateConfig()
{
    mConfig = JsonParser::read(CONFIG_FILENAME);
}

QJsonValue AppChangeEventDriverConfigManager::get(const char*  key)
{
    if (isValid()) {
        return mConfig[key];
    }
}
