#include "statemachine.h"

#include "statenotracking.h"
#include "stateactivetracking.h"
#include "statemachineexception.h"


#include "linuxstatemanager.h"
#include "eventtracker.h"
#include "eventdriverconfiguration.h"

StateMachine::StateMachine() :
    mStateChangeMgr(nullptr),
    mCurrStateKey(StateEnum::ACTIVE_TRACKING),
    mCurrState(nullptr)
{
}

void StateMachine::init()
{
    mStateChangeMgr = std::make_shared<StateChangeManager>();

    auto osStateMgr = std::make_shared<LinuxStateManager>();
    mStateChangeMgr->setOSStateMgr(osStateMgr);
    auto eventTracker = std::make_shared<EventTracker>(osStateMgr);
    mStateChangeMgr->setEventTracker(eventTracker);
    auto conf = std::make_shared<EventDriverConfiguration>();
    mStateChangeMgr->setConfiguration(conf);

    mStateMap.insert(std::make_pair(StateEnum::NO_TRACKING, std::make_shared<StateNoTracking>(this, mStateChangeMgr)));
    mStateMap.insert(std::make_pair(StateEnum::ACTIVE_TRACKING, std::make_shared<StateActiveTracking>(this, mStateChangeMgr)));

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
