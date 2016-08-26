#include <iostream>
#include <string>
#include <X11/Xlib.h>

#include "AppChangeEventDriver.h"


AppChangeEventDriver::AppChangeEventDriver() {}
AppChangeEventDriver::~AppChangeEventDriver() {}

void AppChangeEventDriver::start() {
    std::cout << "AppChangeEventDriver::start()" << std::endl;

    Display* display;
    Window focus;
    char* window_name;
    int revert;

    display = XOpenDisplay(nullptr);
    XGetInputFocus(display, &focus, &revert);
    XFetchName(display, focus, &window_name);

    if (window_name == nullptr) {
        std::cout << "window name error" << std::endl;
        return;
    }

    std::string str_name(window_name);
    std::cout << "app name -->  " << window_name << std::endl;
}
