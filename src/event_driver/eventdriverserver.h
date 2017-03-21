#pragma once

#include "iserver.h"
#include "commontypes.h"

namespace driver {

class EventDriverServer : public IServer
{
public:
    void start() override;
    void stop() override;
    bool isRunning() override;

private:
    volatile bool mIsRunning = false;

};

} // driver
