
#include "Reporter.h"
#include "DataBase.h"
#include "stt_algorithm.h"

#include <iostream>
#include <vector>


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
    auto appList = DataBase::Get().getListOfAppByDay(day);

    for (auto app : appList) {
        std::cout << app << std::endl;
    }
}

void Reporter::makeIntervalReport(const std::string& dayBeg, const std::string& dayEnd) {
    // TODO: implement it
    std::cout << "not implemented" << std::endl;
}
