
#pragma once

#include "timeinfo.h"

#include <vector>
#include <string>
#include <iostream>

#include <QString>

typedef std::vector<std::string> StrVector;

class AppInfo
{
public:
    QString pid;
    QString name;
    QString title;
    TimeInfo timeStarted;
    float duration;
};
