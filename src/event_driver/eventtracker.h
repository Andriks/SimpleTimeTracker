#ifndef EVENTTRACKER_H
#define EVENTTRACKER_H

#include <memory>

#include "commontypes.h"
#include "iosstatemanager.h"

namespace driver {

class EventTracker
{
public:
    EventTracker(std::shared_ptr<IOSStateManager> osStateMgr);

    void forceSendChangeEvent(bool autosave = false, bool idle = false);
    void sendChangeEvent(AppInfo newApp, bool autosave);
    void dump();

    AppInfo getCachedAppInfo();
    AppInfo getCurrAppInfo();
    unsigned int getTimeFromLastSaveMs();
    unsigned int currTimeMs() const;

private:
    std::shared_ptr<IOSStateManager> mOSStateMgr;
    AppInfo mLastApp;
    unsigned int mLastSave;
};

} // driver

#endif // EVENTTRACKER_H
