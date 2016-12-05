#include "appchangeeventdriver.h"
#include "signalhandler.h"

#include <stdio.h>
#include <thread>
#include <chrono>

#include <X11/Xlib.h>


unsigned int AppChangeEventDriver::AUTOSAVE_TIMEOUT_MS = 5*1000*60; // 5min
unsigned int AppChangeEventDriver::UPDATE_TIMEOUT_MS = 1000; // 1sec

void AppChangeEventDriver::start() {
    if (isRunning()) {
        return;
    }

    mIsRunning = true;
    mLastSave = currTimeMs();
    mLastApp = getCurrAppInfo();

    // run event loop
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_TIMEOUT_MS));

        QString pid = exec_cmd("xdotool getactivewindow getwindowpid");
        if (mLastApp.pid != pid) {
            forceSendChangeEvent();
        } else if ( currTimeMs()-mLastSave > AUTOSAVE_TIMEOUT_MS ) {
            forceSendChangeEvent(true);
        }
    }
}

void AppChangeEventDriver::stop() {
    if (isRunning()) {
        mIsRunning = false;
        forceSendChangeEvent(true);
    }
}

bool AppChangeEventDriver::isRunning() {
    return mIsRunning;
}

void AppChangeEventDriver::forceSendChangeEvent(bool autosave) {
    mLastApp.duration = currTimeMs() - mLastApp.timeStarted.toMSecsSinceEpoch();
    mLastApp.duration /= 1000; // msec -> sec

    mLastSave = currTimeMs();
    sendChangeEvent(mLastApp, autosave);
    mLastApp = getCurrAppInfo();
}

void AppChangeEventDriver::sendChangeEvent(AppInfo newApp, bool autosave) {
    SignalHandler::Get().sendChangeAppEvent(newApp, autosave);
}

QString AppChangeEventDriver::exec_cmd(char* cmd) {
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

AppInfo AppChangeEventDriver::getCurrAppInfo() {
    QString pid = exec_cmd("xdotool getactivewindow getwindowpid");
    QString name_request = "ps -p " + pid + " -o comm=";
    QString name = exec_cmd(name_request.toStdString().c_str());
    QString title = exec_cmd("xdotool getwindowfocus getwindowname");

    return AppInfo(pid, name, title, QDateTime::currentDateTime());
}

unsigned int AppChangeEventDriver::currTimeMs() const
{
    return QDateTime::currentMSecsSinceEpoch();
}
