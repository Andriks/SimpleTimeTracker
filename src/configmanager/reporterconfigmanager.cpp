#include "reporterconfigmanager.h"
#include "jsonparser.h"

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
    mConfig = JsonParser::read(CONFIG_FILENAME);
}

QJsonValue ReporterConfigManager::get(const char*  key)
{
    if (isValid()) {
        return mConfig[key];
    }
}


