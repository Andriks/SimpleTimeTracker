
#pragma once

#include "commontypes.h"

#include <QString>

class IDataBase
{
public:
    virtual ~IDataBase() {}
    virtual void write(const AppInfo &newApp, bool autosave) = 0;
    virtual StrVector getListOfAppByDay(const QString& day) = 0;
    virtual float getAppTimeByDay(const QString& appName, const QString& day) = 0;
    virtual float getIdleTimeByDay(const QString &day) = 0;

};
