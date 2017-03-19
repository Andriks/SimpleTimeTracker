#ifndef ACTIVETRACKINGSTATE_H
#define ACTIVETRACKINGSTATE_H

#include <memory>

#include "astate.h"

class StateActiveTracking: public AState
{
public:
    StateActiveTracking(StateMachine *parent, std::shared_ptr<StateChangeManager> stateChangeMgr);

public:
    virtual StateEnum checkNextState();
    virtual std::shared_ptr<IState> goTo(StateEnum state);

protected:
    virtual void procNoStateChange();

private:
    bool needSwitchToNoTracking();
    void procSwitchToNoTracking();
    bool needSwitchToIdleTracking();
    void procSwitchToIdleTracking();

};

#endif // ACTIVETRACKINGSTATE_H
