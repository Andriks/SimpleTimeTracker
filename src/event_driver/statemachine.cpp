#include "statemachine.h"

#include "notrackingstate.h"
#include "activetrackingstate.h"
#include "statemachineexception.h"

#include "linuxstatemanager.h"

StateMachine::StateMachine() :
    mOSStateMgr(nullptr),
    mEventTracker(nullptr),
    mCurrStateKey(StateEnum::ACTIVE_TRACKING),
    mCurrState(nullptr)
{
}

void StateMachine::init()
{
    mOSStateMgr = std::make_shared<LinuxStateManager>();
    mEventTracker = std::make_shared<EventTracker>(mOSStateMgr);
    mConfiguration = std::make_shared<EventDriverConfiguration>();

    mStateMap.insert(std::make_pair(StateEnum::NO_TRACKING, std::make_shared<NoTrackingState>(this, mOSStateMgr, mEventTracker)));
    mStateMap.insert(std::make_pair(StateEnum::ACTIVE_TRACKING, std::make_shared<ActiveTrackingState>(this, mOSStateMgr, mEventTracker)));

    mCurrState = getStatePtr(mCurrStateKey);
}

void StateMachine::procState()
{
    try {
        mCurrStateKey = mCurrState->checkNextState();
        mCurrState = mCurrState->goTo(mCurrStateKey);
    } catch (StateMachineException &e) {
        std::cerr << e.what() << std::endl;
    }

}

StateMachine::state_ptr StateMachine::getStatePtr(StateEnum key)
{
    return mStateMap[key];
}
