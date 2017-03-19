#include "eventdriverconfigmanager.h"
#include "jsonparser.h"

#include <QDebug>

const char* EventDriverConfigManager::CONFIG_FILENAME = "./config/eventdriver.json";
const char* EventDriverConfigManager::REPORT_FROM_KEY = "report_from";
const char* EventDriverConfigManager::REPORT_TILL_KEY = "report_till";
const char* EventDriverConfigManager::MAKS_IDLE_TIME_MS_KEY = "maks_idle_time_ms";

bool EventDriverConfigManager::isValid()
{
    // TODO: implement it
    return true;
}

void EventDriverConfigManager::updateConfig()
{
    mConfig = JsonParser::read(CONFIG_FILENAME);
}

QJsonValue EventDriverConfigManager::get(const char*  key)
{
    if (isValid()) {
        return mConfig[key];
    }
}
