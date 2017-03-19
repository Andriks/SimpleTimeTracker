#include "stateidletracking.h"
#include "statemachineexception.h"

StateIdleTracking::StateIdleTracking(StateMachine *parent,
                                         std::shared_ptr<StateChangeManager> stateChangeMgr) :
    AState(parent, stateChangeMgr)
{
}

StateEnum StateIdleTracking::checkNextState()
{
    StateEnum result = StateEnum::IDLE_TRACKING;
    if (needSwitchToActiveTracking()) {
        result = StateEnum::ACTIVE_TRACKING;
    } else if (needSwitchToNoTracking()) {
        result = StateEnum::NO_TRACKING;
    }
    return result;
}

std::shared_ptr<IState> StateIdleTracking::goTo(StateEnum state)
{
    switch (state) {
    case StateEnum::IDLE_TRACKING:
        // ITSELF, NO STATE CHANGE
        procNoStateChange();
        return mParent->getCurrState(StateEnum::IDLE_TRACKING);
    case StateEnum::ACTIVE_TRACKING:
        procSwitchToActiveTracking();
        return mParent->getCurrState(StateEnum::ACTIVE_TRACKING);
    case StateEnum::NO_TRACKING:
        procSwitchToNoTracking();
        return mParent->getCurrState(StateEnum::NO_TRACKING);
    default:
        throw UnknownStateException();
    }
}

void StateIdleTracking::procNoStateChange()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    auto osStateMgr = mStateChangeMgr->osStateMgr();
    auto conf = mStateChangeMgr->configuration();
    unsigned int autosaveTimeout = conf->getAutosaveTimeoutMs();
    unsigned int maksIdleTime = conf->getMaksIdleTimeMs();

    if (osStateMgr->getIdleTimeMs() > maksIdleTime
            && eventTracker->getTimeFromLastSaveMs() > autosaveTimeout) {
        eventTracker->forceSendChangeEvent(true);
    }
}

bool StateIdleTracking::needSwitchToActiveTracking()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    return (eventTracker->getCurrAppInfo() != eventTracker->getCachedAppInfo());
}

void StateIdleTracking::procSwitchToActiveTracking()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    eventTracker->forceSendChangeEvent(true);
    eventTracker->dump();
}

bool StateIdleTracking::needSwitchToNoTracking()
{
    bool isTrackedTime = mStateChangeMgr->configuration()->isTrackedTime(QTime::currentTime());
    return !isTrackedTime;
}

void StateIdleTracking::procSwitchToNoTracking()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    eventTracker->forceSendChangeEvent(true);
    eventTracker->dump();
}
