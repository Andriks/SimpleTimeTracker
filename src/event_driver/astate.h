#ifndef ASTATE_H
#define ASTATE_H

#include <memory>

#include "istate.h"
#include "iosstatemanager.h"
#include "statemachine.h"


class AState : public IState {
public:
    AState(StateMachine *parent, std::shared_ptr<IOSStateManager> osStateMgr):
        mParent(parent),
        mOSStateMgr(osStateMgr)
    {}


protected:
    StateMachine *mParent;
    std::shared_ptr<IOSStateManager> mOSStateMgr;
};

#endif // ASTATE_H
