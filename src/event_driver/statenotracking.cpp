#include "statenotracking.h"
#include "statemachineexception.h"

StateNoTracking::StateNoTracking(StateMachine *parent,
                                 std::shared_ptr<StateChangeManager> stateChangeMgr) :
    AState(parent, stateChangeMgr)
{
}

StateEnum StateNoTracking::checkNextState()
{
    StateEnum result = StateEnum::NO_TRACKING;
    if (needSwitchToActiveTracking()) {
        result = StateEnum::ACTIVE_TRACKING;
    }
    return result;
}

std::shared_ptr<IState> StateNoTracking::goTo(StateEnum state)
{
    switch (state) {
    case StateEnum::NO_TRACKING:
        // ITSELF, NO STATE CHANGE
        procNoStateChange();
        return mParent->getStatePtr(StateEnum::NO_TRACKING);
    case StateEnum::ACTIVE_TRACKING:
        procSwitchToActiveTracking();
        return mParent->getStatePtr(StateEnum::ACTIVE_TRACKING);
    default:
        throw UnknownStateException();
    }
}

void StateNoTracking::procNoStateChange()
{
    std::cout << "NoTrackingState::procNoStateChange() || " << std::endl;
}

bool StateNoTracking::needSwitchToActiveTracking()
{
    return true;
}

void StateNoTracking::procSwitchToActiveTracking()
{
    std::cout << "NoTrackingState::procSwitchToActiveTracking() || " << std::endl;
}
