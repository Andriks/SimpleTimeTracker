
#pragma once

#include <string>
#include <iostream>

#include "TimeInfo.h"


class AppInfo
{
public:
    std::string pid;
    std::string name;
    std::string title;
    TimeInfo timeStarted;
    float duration;
};
