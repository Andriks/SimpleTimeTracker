#ifndef ASTATE_H
#define ASTATE_H

#include <memory>

#include "istate.h"
#include "statemachine.h"
#include "statechangemanager.h"


class AState : public IState {
public:
    AState(StateMachine *parent, std::shared_ptr<StateChangeManager> stateChangeMgr) :
        mParent(parent),
        mStateChangeMgr(stateChangeMgr)
    {}

protected:
    StateMachine *mParent;
    std::shared_ptr<StateChangeManager> mStateChangeMgr;
};

#endif // ASTATE_H
