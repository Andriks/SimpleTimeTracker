#include "statemachine.h"

#include "statemachineexception.h"
#include "statechangemanager.h"
#include "statenotracking.h"
#include "stateactivetracking.h"

#include "linuxstatemanager.h"
#include "eventtracker.h"
#include "eventdriverconfiguration.h"

StateMachine::StateMachine() :
    mCurrStateKey(StateEnum::NO_TRACKING),
    mCurrState(nullptr)
{
}

void StateMachine::init()
{
    auto stateChangeMgr = std::make_shared<StateChangeManager>();

    auto osStateMgr = std::make_shared<LinuxStateManager>();
    stateChangeMgr->setOSStateMgr(osStateMgr);
    auto eventTracker = std::make_shared<EventTracker>(osStateMgr);
    stateChangeMgr->setEventTracker(eventTracker);
    auto conf = std::make_shared<EventDriverConfiguration>();
    conf->readConfiguration();
    stateChangeMgr->setConfiguration(conf);

    mStateMap.insert(std::make_pair(StateEnum::NO_TRACKING,
                                    std::make_shared<StateNoTracking>(this, stateChangeMgr)));
    mStateMap.insert(std::make_pair(StateEnum::ACTIVE_TRACKING,
                                    std::make_shared<StateActiveTracking>(this, stateChangeMgr)));

    mCurrState = getCurrState(mCurrStateKey);
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

StateMachine::state_ptr StateMachine::getCurrState(StateEnum key)
{
    return mStateMap[key];
}
