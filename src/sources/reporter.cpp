
#include "reporter.h"
#include "database.h"
#include "configmanagerfactory.h"
#include "reporterconfigmanager.h"

#include <algorithm>

#include <QDebug>
#include <QMap>
#include <QString>

const char *Reporter::RED   = "\033[031m";
const char *Reporter::GREEN = "\033[032m";
const char *Reporter::ORANGE= "\033[033m";
const char *Reporter::BLUE  = "\033[034m";
const char *Reporter::AUTO  = "\033[0m";

bool Reporter::checkRequest(const QString &request) const {
    // TODO: implement it
    Q_UNUSED(request)
    return true;
}

void Reporter::doReport(const QString& _request) {
    QString request;
    if (_request.isEmpty()) {
        auto configMgr = ConfigManagerFactory::getConfigFor(ConfigManagerFactory::REPORTER);
        request = configMgr->get(ReporterConfigManager::DEFAULT_REQUEST_KEY).toString();
    } else {
        request = _request;
    }

    if (!checkRequest(request)) {
        qDebug() << "TODO: add error handing - " << "[err] Bad request";
        return;
    }

    QStringList requestVec = request.split(" ", QString::SkipEmptyParts);
    if (requestVec[0] == "-d" || requestVec[0] == "--day") {
        makeDayReport(requestVec[1]);
    } else if (requestVec[0] == "-i" || requestVec[0] == "--interval") {
        makeIntervalReport(requestVec[1], requestVec[2]);
    } else {
        qDebug() << "TODO: add error handing - " << "unknown command " << requestVec[0];
    }
}

void Reporter::makeDayReport(const QString &day) {
    unsigned int totalTime = 0;
    QVector<ItemType> appAndTimeVec;

    auto appList = DataBase::Get().getListOfAppByDay(day);
    for (auto app : appList) {
        unsigned int duration = DataBase::Get().getAppTimeByDay(app, day);
        ItemType item(app, duration);
        appAndTimeVec.push_back(item);

        totalTime += duration;
    }

    std::sort(appAndTimeVec.begin(), appAndTimeVec.end(),
        [](const ItemType &left, const ItemType &right) {
            return left.second > right.second;
        });

    printReport(appAndTimeVec, totalTime);
    printIdle(DataBase::Get().getIdleTimeByDay(day));
}

void Reporter::makeIntervalReport(const QString &dayBeg, const QString &dayEnd) {
    // TODO: implement it
    Q_UNUSED(dayBeg)
    Q_UNUSED(dayEnd)
    qDebug() << "not implemented";
}

void Reporter::printReport(const QVector<ItemType> &vec, const unsigned int inputTotalTime) const {
    unsigned int totalTime = inputTotalTime;
    if (totalTime == 0) {
        for (auto item : vec) {
            totalTime += item.second;
        }
    }

    float totalPercents = 0;
    float totalTimeSec = totalTime/1000; // ms->sec
    for (auto item: vec) {
        float durationSec = (float)item.second/1000; // ms->sec
        float percents = durationSec/totalTimeSec*100;
        totalPercents += percents;
        qDebug() << getColor(percents) << "["
                 << QString::number(percents, 'f', 3) << "% | "
                 << QString::number(durationSec/60, 'f', 3) << "m | "
                 << QString::number(durationSec, 'f', 3) << "s] "
                 << item.first << AUTO;
    }

    qDebug() << RED << "["
             << QString::number(totalPercents, 'f', 0) << "%   | "
             << QString::number(totalTimeSec/60, 'f', 3)  << "m |"
             << QString::number(totalTimeSec/3600, 'f', 3) << "h ]"
             << AUTO;
}

void Reporter::printIdle(const unsigned int idleTimeMs) const
{
    float idleTimeMin = ((float)idleTimeMs/1000) / 60;
    qDebug() << RED << "["
             << "Idle time ->"
             << QString::number(idleTimeMin, 'f', 3)  << "m |"
             << QString::number(idleTimeMin/60, 'f', 3) << "h ]"
             << AUTO;
}

const char *Reporter::getColor(const float persent) const
{
    const char *result = NULL;
    if (persent > 15) {
        result = GREEN;
    } else if (persent > 1) {
        result = BLUE;
    } else {
        result = ORANGE;
    }

    return result;
}
