#include "eventdriverconfigmanager.h"
#include "jsonparser.h"

const char* EventDriverConfigManager::CONFIG_FILENAME = "./config/eventdriver.json";
const char* EventDriverConfigManager::UPDATE_TIMEOUT_MS_KEY = "update_timeout_ms";
const char* EventDriverConfigManager::AUTOSAVE_TIMEOUT_MS_KEY = "autosave_timeout_ms";
const char* EventDriverConfigManager::IDLE_TIMEOUT_MS_KEY = "idle_timeout_ms";
const char* EventDriverConfigManager::REPORT_FROM_KEY = "report_from";
const char* EventDriverConfigManager::REPORT_TILL_KEY = "report_till";

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
