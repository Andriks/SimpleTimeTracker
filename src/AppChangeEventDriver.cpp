#include <iostream>
#include <stdio.h>
#include <thread>
#include <X11/Xlib.h>

#include "AppChangeEventDriver.h"

using namespace aced;

AppChangeEventDriver::AppChangeEventDriver() {}
AppChangeEventDriver::~AppChangeEventDriver() {}

void AppChangeEventDriver::start() {
    AppInfo currApp;
    mLastPoint = std::chrono::system_clock::now();

    // run event loop
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::string pid = exec_cmd("xdotool getactivewindow getwindowpid");

        std::string name_request = "ps -p " + pid + " -o comm=";
        std::string name = exec_cmd(name_request.c_str());

        std::string title = exec_cmd("xdotool getwindowfocus getwindowname");
        auto timeStarted = std::chrono::system_clock::now();

        if (currApp.pid != pid) {
            currApp.pid = pid;
            currApp.name = name;
            currApp.title = title;
            currApp.timeStarted = timeStarted;
            sendChangeEvent(currApp);

            mLastPoint = timeStarted;
        }
    }
}


void AppChangeEventDriver::sendChangeEvent(AppInfo newApp) {
    std::chrono::duration<float> fsec = newApp.timeStarted - mLastPoint;

    std::cout << "duration --> " << fsec.count() << " (sec)" << std::endl;
    std::cout << "=================================" << std::endl;

    std::cout << "[pid:" << newApp.pid << "] --> " << newApp.name << std::endl;
    std::cout << newApp.title << std::endl;
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
