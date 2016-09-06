
#pragma once

#include "IServer.h"
#include "CommonTypes.h"

#include <string>

class AppChangeEventDriver : public IServer
{
public:
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
