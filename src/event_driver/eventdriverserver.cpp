#include "eventdriverserver.h"
#include "signalhandler.h"
#include "configmanagerfactory.h"
#include "eventdriverconfigmanager.h"
#include "statemachine.h"

#include <stdio.h>
#include <thread>
#include <chrono>

#include <X11/Xlib.h>

const unsigned int EventDriverServer::UPDATE_TIMEOUT_MS   = 1000;      // 1 sec

void EventDriverServer::start()
{
    if (isRunning()) {
        return;
    }
    mIsRunning = true;

    StateMachine fsm;
    fsm.init();
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_TIMEOUT_MS));
        fsm.procState();
    }
    // TODO: add fsm.stop() logic
}

void EventDriverServer::stop()
{
    if (isRunning()) {
        mIsRunning = false;
    }
}

bool EventDriverServer::isRunning() {
    return mIsRunning;
}
