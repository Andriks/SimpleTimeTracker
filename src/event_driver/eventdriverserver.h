
#pragma once

#include "iserver.h"
#include "commontypes.h"

class EventDriverServer : public IServer
{
    static const unsigned int UPDATE_TIMEOUT_MS;
//    static const unsigned int AUTOSAVE_TIMEOUT_MS;
//    static const unsigned int MAX_IDLE_TIME_MS;

public:
    void start() override;
    void stop() override;
    bool isRunning() override;

//private:
//    void forceSendChangeEvent(bool autosave = false);
//    void sendChangeEvent(AppInfo newApp, bool autosave);

//    void updateTrackedTime();
//    bool isTrackedTime(const QTime time) const;

//private:
//    QString exec_cmd(char* cmd);
//    AppInfo getCurrAppInfo();
//    unsigned int currTimeMs() const;

private:
    volatile bool mIsRunning = false;
//    bool mIsIdle = false;
//    AppInfo mLastApp;
//    unsigned int mLastSave;
//    QTime mTrackFrom;
//    QTime mTrackTill;

};
