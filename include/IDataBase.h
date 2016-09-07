
#pragma once

#include "CommonTypes.h"

#include <string>

class IDataBase
{
public:
    virtual ~IDataBase() {}
    virtual void write(AppInfo newApp) = 0;
    virtual StrVector getListOfAppByDay(const std::string& day) = 0;

};
