#include "notrackingstate.h"
#include "statemachineexception.h"

NoTrackingState::NoTrackingState(StateMachine *parent,
                                 std::shared_ptr<IOSStateManager> osStateMgr,
                                 std::shared_ptr<EventTracker> eventTracker) :
    AState(parent, osStateMgr, eventTracker)
{
}

StateEnum NoTrackingState::checkNextState()
{
    StateEnum result = StateEnum::NO_TRACKING;
    if (needSwitchToActiveTracking()) {
        result = StateEnum::ACTIVE_TRACKING;
    }
    return result;
}

std::shared_ptr<IState> NoTrackingState::goTo(StateEnum state)
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

void NoTrackingState::procNoStateChange()
{
    std::cout << "NoTrackingState::procNoStateChange() || " << std::endl;
}

bool NoTrackingState::needSwitchToActiveTracking()
{
    return true;
}

void NoTrackingState::procSwitchToActiveTracking()
{
    std::cout << "NoTrackingState::procSwitchToActiveTracking() || " << std::endl;
}
