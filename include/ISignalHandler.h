
#pragma once

#include "CommonTypes.h"

class ISignalHandler
{
public:
    virtual ~ISignalHandler() {}
    virtual void sendChangeAppEvent(AppInfo newApp) = 0;
};
