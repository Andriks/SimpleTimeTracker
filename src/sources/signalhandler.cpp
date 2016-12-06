
#include "signalhandler.h"
#include "database.h"

#include <QDebug>

SignalHandler::SignalHandler() {}

ISignalHandler& SignalHandler::Get() {
    static SignalHandler OnlyOne;
    return OnlyOne;
}

void SignalHandler::sendChangeAppEvent(AppInfo newApp, bool autosave) {
    qDebug() << "[dur:" << (float)newApp.duration/1000 << "] --> " << newApp.name <<
                (autosave ? " (autosave)": "");
    DataBase::Get().write(newApp, autosave);
}
