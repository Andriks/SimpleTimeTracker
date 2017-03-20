#include "statenotracking.h"
#include "statemachineexception.h"

#include "QTime"

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
        break;
    case StateEnum::ACTIVE_TRACKING:
        procSwitchToActiveTracking();
        break;
    default:
        throw UnknownStateException();
    }
    return mParent->getCurrState(state);
}

void StateNoTracking::procNoStateChange()
{
    // do nothing
}

bool StateNoTracking::needSwitchToActiveTracking()
{
    return mStateChangeMgr->configuration()->isTrackedTime(QTime::currentTime());
}

void StateNoTracking::procSwitchToActiveTracking()
{
    std::cout << "[debug] " << "NoTracking -> ActiveTracking" << std::endl;
    mStateChangeMgr->eventTracker()->dump();
}
