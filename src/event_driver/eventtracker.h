#ifndef EVENTTRACKER_H
#define EVENTTRACKER_H

#include <memory>

#include "commontypes.h"
#include "iosstatemanager.h"

class EventTracker
{
public:
    EventTracker(std::shared_ptr<IOSStateManager> osStateMgr);

    void forceSendChangeEvent(bool autosave = false);
    void sendChangeEvent(AppInfo newApp, bool autosave);
    void dump();

    AppInfo getCachedAppInfo();
    AppInfo getCurrAppInfo();
    unsigned int currTimeMs() const;

private:
    std::shared_ptr<IOSStateManager> mOSStateMgr;
    AppInfo mLastApp;
    unsigned int mLastSave;
};

#endif // EVENTTRACKER_H
