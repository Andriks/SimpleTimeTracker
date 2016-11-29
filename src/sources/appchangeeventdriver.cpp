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
    std::chrono::duration<float> fsec = std::chrono::system_clock::now() - mLastApp.timeStarted.toTimePoint();
    mLastApp.duration = fsec.count();
    
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
    auto timeStarted = std::chrono::system_clock::now();

    AppInfo result;
    result.pid = pid;
    result.name = name;
    result.title = title;
    result.timeStarted.init(timeStarted);

    return result;
}
