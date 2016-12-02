
#pragma once

#include "commontypes.h"

#include <QString>
#include <QVector>
#include <QPair>

class Reporter
{
    typedef QPair<QString, float> ItemType;

public:
    bool checkRequest(const QString& request) const;
    void doReport(const QString &request);

private:
    void makeDayReport(const QString& day);
    void makeIntervalReport(const QString& dayBeg, const QString& dayEnd);
    void printReport(const QVector<ItemType>& vec, const float inputTotalTime = 0) const;
        
};
