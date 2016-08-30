
#include "SignalHandler.h"
#include "DataBase.h"

#include <iostream>

SignalHandler::SignalHandler() {}
SignalHandler::~SignalHandler() {}

ISignalHandler& SignalHandler::Instance() {
    static SignalHandler OnlyOne;
    return OnlyOne;
}

void SignalHandler::sendChangeAppEvent(AppInfo newApp) {
    std::cout << "[pid:" << newApp.pid << "] --> " << newApp.name << std::endl;

    IDataBase& db = DataBase::Instance();
    db.write(newApp);
}
