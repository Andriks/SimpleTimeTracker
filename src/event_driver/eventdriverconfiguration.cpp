#include "eventdriverconfiguration.h"
#include "configmanagerfactory.h"
#include "eventdriverconfigmanager.h"

const unsigned int EventDriverConfiguration::DEFAULT_UPDATE_TIMEOUT_MS   = 1000;      // 1 sec
const unsigned int EventDriverConfiguration::DEFAULT_AUTOSAVE_TIMEOUT_MS = 5*1000*60; // 5 min
const QTime EventDriverConfiguration::DEFAULT_TIME_TRACK_FROM            = QTime(8, 0, 0);
const QTime EventDriverConfiguration::DEFAULT_TIME_TRACK_TILL            = QTime(18, 0, 0);

void EventDriverConfiguration::readConfiguration()
{
    mUpdateTimeout = DEFAULT_UPDATE_TIMEOUT_MS;
    mAutosaveTimeout = DEFAULT_AUTOSAVE_TIMEOUT_MS;
    mTrackFrom = DEFAULT_TIME_TRACK_FROM;
    mTrackTill = DEFAULT_TIME_TRACK_TILL;

    auto configMgr = ConfigManagerFactory::getConfigFor(ConfigManagerFactory::APP_CHANGE_EVENT_DRIVER);

    QString updateTimeOutStr = configMgr->get(EventDriverConfigManager::UPDATE_TIMEOUT_MS_KEY).toString();
    if (updateTimeOutStr.size() > 0) {
        mUpdateTimeout = updateTimeOutStr.toInt();
    }

    QString autosaveTimeOutStr = configMgr->get(EventDriverConfigManager::AUTOSAVE_TIMEOUT_MS_KEY).toString();
    if (autosaveTimeOutStr.size() > 0) {
        mAutosaveTimeout = autosaveTimeOutStr.toInt();
    }

    QString reportFromStr = configMgr->get(EventDriverConfigManager::REPORT_FROM_KEY).toString();
    if (reportFromStr.size() > 0) {
        mTrackFrom = QTime::fromString(reportFromStr, "hh:mm:ss");
    }

    QString reportTillStr = configMgr->get(EventDriverConfigManager::REPORT_TILL_KEY).toString();
    if (reportTillStr.size() > 0) {
        mTrackTill = QTime::fromString(reportTillStr, "hh:mm:ss");
    }
}

unsigned int EventDriverConfiguration::getUpdateTimeoutMs()
{
    return mUpdateTimeout;
}

unsigned int EventDriverConfiguration::getAutosaveTimeoutMs()
{
    return mAutosaveTimeout;
}

unsigned int EventDriverConfiguration::getIdleTimeoutMs()
{
    // TODO: add own cofig param for idle
    return mAutosaveTimeout;
}

bool EventDriverConfiguration::isTrackedTime(QTime time)
{
    return (time >= mTrackFrom) && (time < mTrackTill);
}
