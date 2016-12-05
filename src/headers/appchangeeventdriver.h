
#pragma once

#include "Iserver.h"
#include "commontypes.h"

class AppChangeEventDriver : public IServer
{
    static unsigned int AUTOSAVE_TIMEOUT_MS;
    static unsigned int UPDATE_TIMEOUT_MS;

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
    unsigned int currTimeMs() const;

private:
    bool mIsRunning = false;
    AppInfo mLastApp;
    unsigned int mLastSave;

};
