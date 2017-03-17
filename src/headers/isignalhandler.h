
#pragma once

#include "commontypes.h"

class ISignalHandler
{
public:
    virtual ~ISignalHandler() {}
    virtual void sendChangeAppEvent(AppInfo newApp, bool autosave) = 0;
};
