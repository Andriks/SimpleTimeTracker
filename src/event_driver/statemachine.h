#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <map>
#include <memory>

#include "istate.h"
#include "statechangemanager.h"

enum class StateEnum {
    NO_TRACKING = 1,
    ACTIVE_TRACKING = 2,
    IDLE_TRACKING = 3
};

class StateMachine
{
public:
    typedef std::shared_ptr<IState> state_ptr;

public:
    StateMachine();
    void init();
    void procState();
    state_ptr getStatePtr(StateEnum key);

private:
    std::shared_ptr<StateChangeManager> mStateChangeMgr;
    StateEnum mCurrStateKey;
    state_ptr mCurrState;
    std::map<StateEnum, state_ptr> mStateMap;
};

#endif // STATEMACHINE_H
