
#pragma once

#include <iostream>
#include <QDebug>

#include <QDateTime>
#include <QString>
#include <QStringList>


typedef QStringList StrVector;

class AppInfo
{
public:
    AppInfo() {}
    AppInfo(const QString &pidIn, const QString &nameIn, const QString &titleIn,
            const unsigned int &timeStartedIn, const unsigned int durationIn = 0) :
        pid(pidIn),
        name(nameIn),
        title(titleIn),
        timeStarted(timeStartedIn),
        duration(durationIn)
    {}

    bool operator ==(const AppInfo& other) {
        return (pid == other.pid
                    && name == other.name);
    }
    bool operator !=(const AppInfo& other) {
        return (pid != other.pid
                    || name != other.name);
    }


    QString pid;
    QString name;
    QString title;
    unsigned int timeStarted;
    unsigned int duration;
};
