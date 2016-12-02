
#include "reporter.h"
#include "database.h"

#include <algorithm>

#include <QDebug>

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

void Reporter::doReport(const QString& request) {
    if (!checkRequest(request)) {
        qDebug() << "[err] Bad request";
        return;
    }

    QStringList requestVec = request.split(" ", QString::SkipEmptyParts);
    if (requestVec[0] == "-d" || requestVec[0] == "--day") {
        makeDayReport(requestVec[1]);
    } else if (requestVec[0] == "-i" || requestVec[0] == "--interval") {
        makeIntervalReport(requestVec[1], requestVec[2]);
    } else {
        qDebug() << "unknown command " << requestVec[0];
    }
}

void Reporter::makeDayReport(const QString &day) {
    float totalTime = 0;
    QVector<ItemType> appAndTimeVec;

    auto appList = DataBase::Get().getListOfAppByDay(day);
    for (auto app : appList) {
        float duration = DataBase::Get().getAppTimeByDay(app, day);
        ItemType item(app, duration);
        appAndTimeVec.push_back(item);

        totalTime += duration;
    }

    std::sort(appAndTimeVec.begin(), appAndTimeVec.end(),
        [](const ItemType &left, const ItemType &right) {
            return left.second > right.second;
        });

    printReport(appAndTimeVec, totalTime);
}

void Reporter::makeIntervalReport(const QString &dayBeg, const QString &dayEnd) {
    // TODO: implement it
    Q_UNUSED(dayBeg)
    Q_UNUSED(dayEnd)
    qDebug() << "not implemented";
}

void Reporter::printReport(const QVector<ItemType> &vec, const float inputTotalTime) const {
    float totalTime = inputTotalTime;
    if (totalTime == 0) {
        for (auto item : vec) {
            totalTime += item.second;
        }
    }

    float totalPercents = 0;
    for (auto item: vec) {
        float percents = item.second/totalTime*100;
        totalPercents += percents;
        qDebug() << getColor(percents) << "[" << percents << "% | " << item.second/60 << "m | " << item.second << "s] "
                 << item.first << AUTO;
    }

    qDebug() << RED << "[" << totalPercents << "% | " << totalTime/60 << "m | " << totalTime << "s]" << AUTO;
}

const char *Reporter::getColor(const float persent) const
{
    const char *result = NULL;
    if (persent > 15) {
        result = GREEN;
    } else if (persent > 10) {
        result = BLUE;
    } else {
        result = ORANGE;
    }

    return result;
}
