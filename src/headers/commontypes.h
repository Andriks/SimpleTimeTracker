
#pragma once

#include "timeinfo.h"

#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::string> StrVector;

class AppInfo
{
public:
    std::string pid;
    std::string name;
    std::string title;
    TimeInfo timeStarted;
    float duration;
};
