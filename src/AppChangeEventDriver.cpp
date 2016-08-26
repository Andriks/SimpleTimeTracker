#include <iostream>
#include <stdio.h>
#include <thread>
#include <X11/Xlib.h>

#include "AppChangeEventDriver.h"


AppChangeEventDriver::AppChangeEventDriver() {}
AppChangeEventDriver::~AppChangeEventDriver() {}

void AppChangeEventDriver::start() {
    std::cout << "[beg] AppChangeEventDriver::start()" << std::endl;
        
        std::string pid_cache;
        std::string title_cache;
        std::string appname_cache;

    // run event loop
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::string pid = exec_cmd("xdotool getactivewindow getwindowpid");
        std::string title = exec_cmd("xdotool getwindowfocus getwindowname");

        std::string appname_request = "ps -p " + pid + " -o comm=";
        std::string appname = exec_cmd(appname_request.c_str());

        if (pid_cache != pid) {
            pid_cache = pid;
            title_cache = title;
            appname_cache = appname;

            std::cout << "[pid:" << pid << "] --> " << appname << std::endl;
            std::cout << title << std::endl;
            std::cout << "=================================" << std::endl;

        }
    }

    std::cout << "[end] AppChangeEventDriver::start()" << std::endl;
}

std::string AppChangeEventDriver::exec_cmd(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
    }
    pclose(pipe);
    return result.substr(0, result.size()-1);
}
