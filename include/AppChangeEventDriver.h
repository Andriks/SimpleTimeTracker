
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
    void stop();

protected:
    void forceSendChangeEvent(AppInfo newApp);
    void sendChangeEvent(AppInfo newApp);
    std::string exec_cmd(char* cmd);

    AppInfo getCurrAppInfo();

private:

};


} // aced
