
#pragma once

#include <string>

#include "CommonTypes.h"
#include "IServer.h"

namespace aced {

class AppChangeEventDriver : public IServer
{
public:
    AppChangeEventDriver();
    ~AppChangeEventDriver();
    
    void start() override;
    void stop() override;
    bool isRunning() override;

protected:
    virtual void forceSendChangeEvent();
    virtual void sendChangeEvent(AppInfo newApp);

private:
    std::string exec_cmd(char* cmd);
    AppInfo getCurrAppInfo();

private:
    bool mIsRunning = false;
    AppInfo mLastApp;

};


} // aced
