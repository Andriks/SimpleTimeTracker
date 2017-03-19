#include "activetrackingstate.h"
#include "statemachineexception.h"

ActiveTrackingState::ActiveTrackingState(StateMachine *parent,
                                         std::shared_ptr<IOSStateManager> osStateMgr,
                                         std::shared_ptr<EventTracker> eventTracker) :
    AState(parent, osStateMgr, eventTracker)
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
    if (mEventTracker->getCachedAppInfo() != mEventTracker->getCurrAppInfo()) {
        mEventTracker->forceSendChangeEvent(false);
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
