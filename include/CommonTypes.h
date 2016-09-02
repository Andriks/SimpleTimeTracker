
#pragma once

#include <chrono>
#include <string>

#include "TimeInfo.h"

typedef std::chrono::system_clock::time_point time_point;

class AppInfo
{
public:
    std::string pid;
    std::string name;
    std::string title;
    time_point timeStarted;
    TimeInfo timeStarted_;
    float duration;
};
