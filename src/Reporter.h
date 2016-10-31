
#pragma once

#include "CommonTypes.h"

#include <string>

class Reporter
{
    typedef std::pair<std::string, float> ItemType;

public:
    bool checkRequest(const std::string& request) const;
    void doReport(const std::string& request);

private:
    void makeDayReport(const std::string& day);
    void makeIntervalReport(const std::string& dayBeg, const std::string& dayEnd);
    void printReport(const std::vector<ItemType>& vec, const float inputTotalTime = 0) const;
        
};
