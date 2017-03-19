
#pragma once

#include "iserver.h"
#include "commontypes.h"

class EventDriverServer : public IServer
{
    static const unsigned int UPDATE_TIMEOUT_MS;

public:
    void start() override;
    void stop() override;
    bool isRunning() override;

private:
    volatile bool mIsRunning = false;

};
