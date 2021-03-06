
#pragma once

#include "commontypes.h"

#include <QString>
#include <QVector>
#include <QPair>

class Reporter
{
    typedef QPair<QString, unsigned int> ItemType;

    const static char *RED;
    const static char *GREEN;
    const static char *ORANGE;
    const static char *BLUE;
    const static char *AUTO;
public:
    bool checkRequest(const QString& request) const;
    void doReport(const QString &_request);

private:
    void makeDayReport(const QString& day);
    void makeProductivityDayReport(const QString& day);
    void makeIntervalReport(const QString& dayBeg, const QString& dayEnd);
    void printIdle(const unsigned int idleTimeMs) const;
    void printTotal(const unsigned int totalTimeMs) const;

    QString beautyTime(const unsigned int timeMs) const;
    QString beautyRersents(const unsigned int timeMs, const unsigned int totalTimeMs) const;

        
};
