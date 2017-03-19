#ifndef ASTATE_H
#define ASTATE_H

#include <memory>

#include "istate.h"
#include "iosstatemanager.h"
#include "statemachine.h"


class AState : public IState {
public:
    AState(StateMachine *parent,
           std::shared_ptr<IOSStateManager> osStateMgr,
           std::shared_ptr<EventTracker> eventTracker):
        mParent(parent),
        mOSStateMgr(osStateMgr),
        mEventTracker(eventTracker)
    {}


protected:
    StateMachine *mParent;
    std::shared_ptr<IOSStateManager> mOSStateMgr;
    std::shared_ptr<EventTracker> mEventTracker;
};

#endif // ASTATE_H
