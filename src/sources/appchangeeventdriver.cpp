#include "appchangeeventdriver.h"
#include "signalhandler.h"

#include <stdio.h>
#include <thread>
#include <chrono>

#include <X11/Xlib.h>


void AppChangeEventDriver::start() {
    if (isRunning()) {
        return;
    }

    mIsRunning = true;
    mLastApp = getCurrAppInfo();

    // run event loop
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        QString pid = exec_cmd("xdotool getactivewindow getwindowpid");
        if (mLastApp.pid != pid) {
            forceSendChangeEvent();
        }
    }
}

void AppChangeEventDriver::stop() {
    if (isRunning()) {
        mIsRunning = false;
        forceSendChangeEvent();
    }
}

bool AppChangeEventDriver::isRunning() {
    return mIsRunning;
}

void AppChangeEventDriver::forceSendChangeEvent() {
    mLastApp.duration = QDateTime::currentMSecsSinceEpoch() - mLastApp.timeStarted.toMSecsSinceEpoch();
    mLastApp.duration /= 1000; // msec -> sec

    sendChangeEvent(mLastApp);
    mLastApp = getCurrAppInfo();
}

void AppChangeEventDriver::sendChangeEvent(AppInfo newApp) {
    SignalHandler::Get().sendChangeAppEvent(newApp);
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
