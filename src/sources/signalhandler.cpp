
#include "signalhandler.h"
#include "database.h"

#include <iostream>

SignalHandler::SignalHandler() {}

ISignalHandler& SignalHandler::Get() {
    static SignalHandler OnlyOne;
    return OnlyOne;
}

void SignalHandler::sendChangeAppEvent(AppInfo newApp) {
    std::cout << "[pid:" << newApp.pid << "] --> " << newApp.name << std::endl;
    DataBase::Get().write(newApp);
}
