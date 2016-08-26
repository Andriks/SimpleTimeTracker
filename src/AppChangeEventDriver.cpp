#include <iostream>
#include <stdio.h>
#include <thread>
#include <X11/Xlib.h>

#include "AppChangeEventDriver.h"


AppChangeEventDriver::AppChangeEventDriver() {}
AppChangeEventDriver::~AppChangeEventDriver() {}

void AppChangeEventDriver::start() {
    std::cout << "[beg] AppChangeEventDriver::start()" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::string title = exec_cmd("xdotool getwindowfocus getwindowname");
    std::string pid = exec_cmd("xdotool getactivewindow getwindowpid");

    std::string app_name_request = "ps -p " + pid + " -o comm=";
    std::string app_name = exec_cmd(app_name_request.c_str());
    
    std::cout << "title    --> " << title << std::endl
              << "app name --> " << app_name << std::endl
              << "pid      --> " << pid << std::endl;

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
