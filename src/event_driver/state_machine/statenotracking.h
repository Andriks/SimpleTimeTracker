#ifndef NOTRACKINGSTATE_H
#define NOTRACKINGSTATE_H

#include <memory>

#include "astate.h"

class StateNoTracking: public AState
{
public:
    StateNoTracking(StateMachine *parent, std::shared_ptr<StateChangeManager> stateChangeMgr);

public:
    virtual StateEnum checkNextState();
    virtual std::shared_ptr<IState> goTo(StateEnum state);

protected:
    virtual void procNoStateChange();

private:
    bool needSwitchToActiveTracking();
    void procSwitchToActiveTracking();

};

#endif // NOTRACKINGSTATE_H
