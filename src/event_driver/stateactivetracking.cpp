#include "stateactivetracking.h"
#include "statemachineexception.h"

StateActiveTracking::StateActiveTracking(StateMachine *parent,
                                         std::shared_ptr<StateChangeManager> stateChangeMgr) :
    AState(parent, stateChangeMgr)
{
}

StateEnum StateActiveTracking::checkNextState()
{
    StateEnum result = StateEnum::ACTIVE_TRACKING;
    if (needSwitchToNoTracking()) {
        result = StateEnum::NO_TRACKING;
    } else if (needSwitchToIdleTracking()) {
        result = StateEnum::IDLE_TRACKING;
    }
    return result;
}

std::shared_ptr<IState> StateActiveTracking::goTo(StateEnum state)
{
    switch (state) {
    case StateEnum::ACTIVE_TRACKING:
        // ITSELF, NO STATE CHANGE
        procNoStateChange();
        break;
    case StateEnum::NO_TRACKING:
        procSwitchToNoTracking();
        break;
    case StateEnum::IDLE_TRACKING:
        procSwitchToIdleTracking();
        break;
    default:
        throw UnknownStateException();
    }
    return mParent->getCurrState(state);
}

void StateActiveTracking::procNoStateChange()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    auto conf = mStateChangeMgr->configuration();

    if (eventTracker->getCachedAppInfo() != eventTracker->getCurrAppInfo()) {
        eventTracker->forceSendChangeEvent(false);
    } else if (eventTracker->getTimeFromLastSaveMs() > conf->getAutosaveTimeoutMs()) {
        eventTracker->forceSendChangeEvent(true);
    }
}

bool StateActiveTracking::needSwitchToNoTracking()
{
    bool isTrackedTime = mStateChangeMgr->configuration()->isTrackedTime(QTime::currentTime());
    return !isTrackedTime;
}

void StateActiveTracking::procSwitchToNoTracking()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    eventTracker->forceSendChangeEvent(true);
    eventTracker->dump();
}

bool StateActiveTracking::needSwitchToIdleTracking()
{
    auto conf = mStateChangeMgr->configuration();
    auto osStateMgr = mStateChangeMgr->osStateMgr();

    return (osStateMgr->getIdleTimeMs() > conf->getAutosaveTimeoutMs());
}

void StateActiveTracking::procSwitchToIdleTracking()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    eventTracker->forceSendChangeEvent(true);
    eventTracker->dump();
}
