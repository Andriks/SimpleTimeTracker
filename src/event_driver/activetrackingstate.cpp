#include "activetrackingstate.h"
#include "statemachineexception.h"

ActiveTrackingState::ActiveTrackingState(StateMachine *parent, std::shared_ptr<IOSStateManager> osStateMgr) :
    AState(parent, osStateMgr)
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
        return mParent->getStatePtr(StateEnum::NO_TRACKING);
    case StateEnum::NO_TRACKING:
        procSwitchToNoTracking();
        return mParent->getStatePtr(StateEnum::NO_TRACKING);
    default:
        throw UnknownStateException();
    }
}

void ActiveTrackingState::procNoStateChange()
{
    std::cout << "ActiveTrackingState::procNoStateChange() || " << std::endl;
}

bool ActiveTrackingState::needSwitchToNoTracking()
{
    return true;
}

void ActiveTrackingState::procSwitchToNoTracking()
{
    std::cout << "NoTrackingState::procSwitchToNoTracking() || " << std::endl;
}
