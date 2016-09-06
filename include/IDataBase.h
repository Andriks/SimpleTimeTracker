
#pragma once

#include "CommonTypes.h"

class IDataBase
{
public:
    virtual ~IDataBase() {}
    virtual void write(AppInfo newApp) = 0;

};
