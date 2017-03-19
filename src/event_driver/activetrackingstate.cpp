#include "activetrackingstate.h"
#include "statemachineexception.h"

ActiveTrackingState::ActiveTrackingState(StateMachine *parent,
                                         std::shared_ptr<StateChangeManager> stateChangeMgr) :
    AState(parent, stateChangeMgr)
{
}

StateEnum ActiveTrackingState::checkNextState()
{
    StateEnum result = StateEnum::ACTIVE_TRACKING;
    if (needSwitchToNoTracking()) {
        result = StateEnum::NO_TRACKING;
    }
    return result;
}

std::shared_ptr<IState> ActiveTrackingState::goTo(StateEnum state)
{
    switch (state) {
    case StateEnum::ACTIVE_TRACKING:
        // ITSELF, NO STATE CHANGE
        procNoStateChange();
        return mParent->getStatePtr(StateEnum::ACTIVE_TRACKING);
    case StateEnum::NO_TRACKING:
        procSwitchToNoTracking();
        return mParent->getStatePtr(StateEnum::NO_TRACKING);
    default:
        throw UnknownStateException();
    }
}

void ActiveTrackingState::procNoStateChange()
{
    auto eventTracker = mStateChangeMgr->eventTracker();
    if (eventTracker->getCachedAppInfo() != eventTracker->getCurrAppInfo()) {
        eventTracker->forceSendChangeEvent(false);
    }
}

bool ActiveTrackingState::needSwitchToNoTracking()
{
    return false;
}

void ActiveTrackingState::procSwitchToNoTracking()
{
    std::cout << "NoTrackingState::procSwitchToNoTracking() || " << std::endl;
}
