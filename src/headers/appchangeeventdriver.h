
#pragma once

#include "Iserver.h"
#include "commontypes.h"

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
    QString exec_cmd(char* cmd);
    AppInfo getCurrAppInfo();

private:
    bool mIsRunning = false;
    AppInfo mLastApp;

};
