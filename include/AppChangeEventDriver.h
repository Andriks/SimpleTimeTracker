
#pragma once

#include <string>

#include "CommonTypes.h"

namespace aced {

class AppChangeEventDriver
{
public:
    AppChangeEventDriver();
    ~AppChangeEventDriver();
    
    void start();

protected:
    void sendChangeEvent(AppInfo newApp);
    std::string exec_cmd(char* cmd);

private:
    time_point mLastPoint;

};


} // aced
