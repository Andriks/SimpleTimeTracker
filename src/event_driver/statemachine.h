#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <map>
#include <memory>

#include "istate.h"
#include "iosstatemanager.h"

enum class StateEnum {
    NO_TRACKING = 1,
    ACTIVE_TRACKING = 2,
    IDLE_TRACKING = 3
};

class StateMachine
{
public:
    typedef std::shared_ptr<IState> state_ptr;
    typedef std::shared_ptr<IOSStateManager> driver_ptr;

public:
    StateMachine();
    void init();
    void procState();
    state_ptr getStatePtr(StateEnum key);

private:
    driver_ptr mOSStateMgr;
    StateEnum mCurrStateKey;
    state_ptr mCurrState;
    std::map<StateEnum, state_ptr> mStateMap;
};

#endif // STATEMACHINE_H
