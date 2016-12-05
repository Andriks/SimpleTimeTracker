
#pragma once

#include "Iserver.h"
#include "commontypes.h"


class AppChangeEventDriver : public IServer
{
public:
    void start() override;
    void stop() override;
    bool isRunning() override;

protected:
    virtual void forceSendChangeEvent(bool autosave = false);
    virtual void sendChangeEvent(AppInfo newApp, bool autosave);

private:
    QString exec_cmd(char* cmd);
    AppInfo getCurrAppInfo();

private:
    bool mIsRunning = false;
    AppInfo mLastApp;

};
