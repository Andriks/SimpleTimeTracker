
#pragma once

#include "iserver.h"
#include "commontypes.h"

class EventDriverServer : public IServer
{
public:
    void start() override;
    void stop() override;
    bool isRunning() override;

private:
    volatile bool mIsRunning = false;

};
