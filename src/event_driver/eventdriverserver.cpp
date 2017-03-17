#include "eventdriverserver.h"
#include "signalhandler.h"
#include "configmanagerfactory.h"
#include "eventdriverconfigmanager.h"

#include <stdio.h>
#include <thread>
#include <chrono>

#include <X11/Xlib.h>

const unsigned int EventDriverServer::UPDATE_TIMEOUT_MS   = 1000;      // 1 sec
const unsigned int EventDriverServer::AUTOSAVE_TIMEOUT_MS = 5*1000*60; // 5 min
const unsigned int EventDriverServer::MAX_IDLE_TIME_MS    = 5*1000*60; // 5 min

void EventDriverServer::start()
{
    if (isRunning()) {
        return;
    }

    updateTrackedTime();

    mIsRunning = true;
    mLastSave = currTimeMs();
    mLastApp = getCurrAppInfo();

    // run event loop
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_TIMEOUT_MS));

        if (!isTrackedTime(QDateTime::currentDateTime().time())) {
            if (!mIsIdle) {
                forceSendChangeEvent(true);
                mIsIdle = true;
            }
            continue;
        }

        unsigned int idleTimeMs = exec_cmd("xprintidle").toUInt();
        if (idleTimeMs > MAX_IDLE_TIME_MS) {
            if (!mIsIdle) {
                forceSendChangeEvent(true);
                mIsIdle = true;
                mLastApp = AppInfo("-1", "idle", "", currTimeMs());
            }
            continue;
        } else {
            if (mIsIdle) {
                forceSendChangeEvent(true);
                mIsIdle = false;
            }

            QString pid = exec_cmd("xdotool getactivewindow getwindowpid");
            if (mLastApp.pid != pid) {
                forceSendChangeEvent();
            } else if ( currTimeMs()-mLastSave > AUTOSAVE_TIMEOUT_MS ) {
                forceSendChangeEvent(true);
            }
        }

    }
}

void EventDriverServer::stop()
{
    if (isRunning()) {
        mIsRunning = false;
        forceSendChangeEvent(true);
    }
}

bool EventDriverServer::isRunning() {
    return mIsRunning;
}

void EventDriverServer::forceSendChangeEvent(bool autosave)
{


    mLastApp.duration = currTimeMs() - mLastApp.timeStarted;

    mLastSave = currTimeMs();
    sendChangeEvent(mLastApp, autosave);
    mLastApp = getCurrAppInfo();
}

void EventDriverServer::sendChangeEvent(AppInfo newApp, bool autosave)
{
    SignalHandler::Get().sendChangeAppEvent(newApp, autosave);
}

void EventDriverServer::updateTrackedTime()
{
    auto configMgr = ConfigManagerFactory::getConfigFor(ConfigManagerFactory::APP_CHANGE_EVENT_DRIVER);
    auto reportFromStr = configMgr->get(EventDriverConfigManager::REPORT_FROM_KEY).toString();
    auto reportTillStr = configMgr->get(EventDriverConfigManager::REPORT_TILL_KEY).toString();

    mTrackFrom = QTime::fromString(reportFromStr, "hh:mm:ss");
    mTrackTill = QTime::fromString(reportTillStr, "hh:mm:ss");
}

bool EventDriverServer::isTrackedTime(const QTime time) const
{
    return (time >= mTrackFrom) && (time < mTrackTill);
}

QString EventDriverServer::exec_cmd(char* cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "ERROR\n";
    }

    char buffer[128];
    QString result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }

    pclose(pipe);
    // remove last symbol '\n' before return
    return result.remove(result.size()-1, 1);
}

AppInfo EventDriverServer::getCurrAppInfo()
{
    QString pid = exec_cmd("xdotool getactivewindow getwindowpid");
    QString name_request = "ps -p " + pid + " -o comm=";
    QString name = exec_cmd(name_request.toStdString().c_str());
    QString title = exec_cmd("xdotool getwindowfocus getwindowname");

    return AppInfo(pid, name, title, currTimeMs());
}

unsigned int EventDriverServer::currTimeMs() const
{
    return QDateTime::currentMSecsSinceEpoch();
}
