
#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <QDateTime>
#include <QString>

typedef std::vector<std::string> StrVector;

class AppInfo
{
public:
    AppInfo() {}
    AppInfo(const QString &pidIn, const QString &nameIn, const QString &titleIn,
            const QDateTime &timeStartedIn, const float durationIn = 0) :
        pid(pidIn),
        name(nameIn),
        title(titleIn),
        timeStarted(timeStartedIn),
        duration(durationIn)
    {}

    QString pid;
    QString name;
    QString title;
    QDateTime timeStarted;
    float duration;
};
