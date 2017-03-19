#include "eventtracker.h"

#include <QString>
#include <QDateTime>

#include "signalhandler.h"

EventTracker::EventTracker(std::shared_ptr<IOSStateManager> osStateMgr) :
    mOSStateMgr(osStateMgr)
{
    mLastApp = getCurrAppInfo();
}

void EventTracker::forceSendChangeEvent(bool autosave)
{
    mLastApp.duration = currTimeMs() - mLastApp.timeStarted;

    mLastSave = currTimeMs();
    sendChangeEvent(mLastApp, autosave);
    mLastApp = getCurrAppInfo();
}

void EventTracker::sendChangeEvent(AppInfo newApp, bool autosave)
{
    SignalHandler::Get().sendChangeAppEvent(newApp, autosave);
}

AppInfo EventTracker::getCachedAppInfo()
{
    return mLastApp;
}

AppInfo EventTracker::getCurrAppInfo()
{
    QString pid = mOSStateMgr->getLastAppPid();
    QString name = mOSStateMgr->getLastAppName();
    QString title = mOSStateMgr->getLastAppTitle();

    return AppInfo(pid, name, title, currTimeMs());
}

unsigned int EventTracker::currTimeMs() const
{
    return QDateTime::currentMSecsSinceEpoch();
}
