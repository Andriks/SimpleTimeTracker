#include "AppChangeEventDriver.h"
#include "SignalHandler.h"

#include <stdio.h>
#include <thread>
#include <chrono>

#include <X11/Xlib.h>

using namespace aced;

AppChangeEventDriver::AppChangeEventDriver() {}
AppChangeEventDriver::~AppChangeEventDriver() {}

void AppChangeEventDriver::start() {
    if (isRunning()) {
        return;
    }

    mIsRunning = true;
    mLastApp = getCurrAppInfo();

    // run event loop
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::string pid = exec_cmd("xdotool getactivewindow getwindowpid");
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
    ISignalHandler& sigHandler = SignalHandler::Instance();
    sigHandler.sendChangeAppEvent(newApp);
}

std::string AppChangeEventDriver::exec_cmd(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "ERROR\n";
    }

    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }

    pclose(pipe);
    // remove last symbol '\n' before return
    return result.substr(0, result.size()-1);
}

AppInfo AppChangeEventDriver::getCurrAppInfo() {
    std::string pid = exec_cmd("xdotool getactivewindow getwindowpid");

    std::string name_request = "ps -p " + pid + " -o comm=";
    std::string name = exec_cmd(name_request.c_str());

    std::string title = exec_cmd("xdotool getwindowfocus getwindowname");
    auto timeStarted = std::chrono::system_clock::now();

    AppInfo result;
    result.pid = pid;
    result.name = name;
    result.title = title;
    result.timeStarted.init(timeStarted);

    return result;
}
