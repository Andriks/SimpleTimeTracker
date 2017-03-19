#include "statechangemanager.h"

StateChangeManager::StateChangeManager() :
    mOSStateMgr(nullptr),
    mEventTracker(nullptr),
    mConfiguration(nullptr)
{
}

std::shared_ptr<IOSStateManager> StateChangeManager::osStateMgr() const
{
    return mOSStateMgr;
}

void StateChangeManager::setOSStateMgr(const std::shared_ptr<IOSStateManager> &osStateMgr)
{
    mOSStateMgr = osStateMgr;
}

std::shared_ptr<EventTracker> StateChangeManager::eventTracker() const
{
    return mEventTracker;
}

void StateChangeManager::setEventTracker(const std::shared_ptr<EventTracker> &eventTracker)
{
    mEventTracker = eventTracker;
}

std::shared_ptr<EventDriverConfiguration> StateChangeManager::configuration() const
{
    return mConfiguration;
}

void StateChangeManager::setConfiguration(const std::shared_ptr<EventDriverConfiguration> &configuration)
{
    mConfiguration = configuration;
}
