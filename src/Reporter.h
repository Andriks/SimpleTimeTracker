
#pragma once

#include "CommonTypes.h"

#include <string>

class Reporter
{
public:
    bool checkRequest(const std::string& request) const;
    void doReport(const std::string& request);

private:
    void makeDayReport(const std::string& day);
    void makeIntervalReport(const std::string& dayBeg, const std::string& dayEnd);
        
};
