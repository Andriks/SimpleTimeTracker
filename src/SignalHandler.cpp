
#include "SignalHandler.h"

#include <iostream>

SignalHandler::SignalHandler() {}
SignalHandler::~SignalHandler() {}

ISignalHandler& SignalHandler::Instance() {
    static SignalHandler OnlyOne;
    return OnlyOne;
}

void SignalHandler::sendChangeAppEvent(AppInfo newApp) {
    std::cout << "SignalHandler::sendChangeAppEvent()" << std::endl;
}
