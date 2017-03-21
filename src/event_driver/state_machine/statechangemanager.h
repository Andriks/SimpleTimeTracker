#ifndef STATECHANGEMANAGER_H
#define STATECHANGEMANAGER_H

#include <memory>

#include "iosstatemanager.h"
#include "eventtracker.h"
#include "eventdriverconfiguration.h"

namespace driver {

class StateChangeManager
{
public:
    StateChangeManager();

    std::shared_ptr<IOSStateManager> osStateMgr() const;
    void setOSStateMgr(const std::shared_ptr<IOSStateManager> &osStateMgr);

    std::shared_ptr<EventTracker> eventTracker() const;
    void setEventTracker(const std::shared_ptr<EventTracker> &eventTracker);

    std::shared_ptr<EventDriverConfiguration> configuration() const;
    void setConfiguration(const std::shared_ptr<EventDriverConfiguration> &configuration);

private:
    std::shared_ptr<IOSStateManager> mOSStateMgr;
    std::shared_ptr<EventTracker> mEventTracker;
    std::shared_ptr<EventDriverConfiguration> mConfiguration;
};

} // driver

#endif // STATECHANGEMANAGER_H
