
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
    if (requestVec[0] == "-d") {
        auto appList = DataBase::Get().getListOfApp(requestVec[1]);
        
        for (auto app : appList) {
            std::cout << app << std::endl;
        }
    } else {
        std::cout << "unknown command " << requestVec[0] << std::endl;
    }
}

