#include "eventdriverserver.h"

#include <thread>
#include <chrono>

#include <X11/Xlib.h>

#include "statemachine.h"
#include "eventdriverconfiguration.h"

namespace driver {

void EventDriverServer::start()
{
    if (isRunning()) {
        return;
    }
    mIsRunning = true;

    EventDriverConfiguration conf;
    conf.readConfiguration();
    const unsigned int timeout = conf.getUpdateTimeoutMs();

    StateMachine fsm;
    fsm.init();
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
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

} // driver
