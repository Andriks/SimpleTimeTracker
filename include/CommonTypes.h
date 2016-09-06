
#pragma once

#include "TimeInfo.h"

#include <string>
#include <iostream>


class AppInfo
{
public:
    std::string pid;
    std::string name;
    std::string title;
    TimeInfo timeStarted;
    float duration;
};
