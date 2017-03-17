#include "statemachine.h"

#include "notrackingstate.h"
#include "activetrackingstate.h"
#include "statemachineexception.h"

#include "linuxstatemanager.h"

StateMachine::StateMachine() :
    mOSStateMgr(nullptr),
    mCurrStateKey(StateEnum::NO_TRACKING),
    mCurrState(nullptr)
{
}

void StateMachine::init()
{
    mOSStateMgr = std::make_shared<LinuxStateManager>();

    mStateMap.insert(std::make_pair(StateEnum::NO_TRACKING, std::make_shared<NoTrackingState>(this, mOSStateMgr)));
    mStateMap.insert(std::make_pair(StateEnum::ACTIVE_TRACKING, std::make_shared<ActiveTrackingState>(this, mOSStateMgr)));

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
