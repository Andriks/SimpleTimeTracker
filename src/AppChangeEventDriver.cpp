#include <iostream>
#include <stdio.h>
#include <thread>
#include <X11/Xlib.h>

#include "AppChangeEventDriver.h"


AppChangeEventDriver::AppChangeEventDriver() {}
AppChangeEventDriver::~AppChangeEventDriver() {}

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
    return result;
}

void AppChangeEventDriver::start() {
    std::cout << "[beg] AppChangeEventDriver::start()" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::string result = exec_cmd("xdotool getwindowfocus getwindowname");
    std::cout << "-->" << result << "<--" << std::endl; 

    std::cout << "[end] AppChangeEventDriver::start()" << std::endl;
}
