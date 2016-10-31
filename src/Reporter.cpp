
#include "Reporter.h"
#include "DataBase.h"
#include "stt_algorithm.h"

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


bool Reporter::checkRequest(const std::string& request) const {
    // TODO: implement it
    return true;
}

void Reporter::doReport(const std::string& request) {
    if (!checkRequest(request)) {
        std::cout << "[err] Bad request" << std::endl;
        return;
    }

    auto requestVec = algo::split(request);
    if (requestVec[0] == "-d" || requestVec[0] == "--day") {
        makeDayReport(requestVec[1]);
    } else if (requestVec[0] == "-i" || requestVec[0] == "--interval") {
        makeIntervalReport(requestVec[1], requestVec[2]);
    } else {
        std::cout << "unknown command " << requestVec[0] << std::endl;
    }
}

void Reporter::makeDayReport(const std::string& day) {
    float totalTime = 0;
    std::vector<ItemType> appAndTimeVec;

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

void Reporter::makeIntervalReport(const std::string& dayBeg, const std::string& dayEnd) {
    // TODO: implement it
    std::cout << "not implemented" << std::endl;
}

void Reporter::printReport(const std::vector<ItemType>& vec, const float inputTotalTime) const {
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
        std::cout << "[" << percents << "% | " << item.second/60 << "m | " << item.second << "s] "
                  << item.first << std::endl;
    }

    std::cout << "[" << totalPercents << "% | " << totalTime/60 << "m | " << totalTime << "s]" << std::endl;
}
