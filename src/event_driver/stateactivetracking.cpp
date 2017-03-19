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
    }
    return result;
}

std::shared_ptr<IState> StateActiveTracking::goTo(StateEnum state)
{
    switch (state) {
    case StateEnum::ACTIVE_TRACKING:
        // ITSELF, NO STATE CHANGE
        procNoStateChange();
        return mParent->getCurrState(StateEnum::ACTIVE_TRACKING);
    case StateEnum::NO_TRACKING:
        procSwitchToNoTracking();
        return mParent->getCurrState(StateEnum::NO_TRACKING);
    default:
        throw UnknownStateException();
    }
}

void StateActiveTracking::procNoStateChange()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    if (eventTracker->getCachedAppInfo() != eventTracker->getCurrAppInfo()) {
        eventTracker->forceSendChangeEvent(false);
    }
}

bool StateActiveTracking::needSwitchToNoTracking()
{
    return false;
}

void StateActiveTracking::procSwitchToNoTracking()
{
    std::cout << "NoTrackingState::procSwitchToNoTracking() || " << std::endl;
}
