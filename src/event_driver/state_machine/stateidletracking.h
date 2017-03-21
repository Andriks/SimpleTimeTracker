#ifndef STATEIDLETRACKING_H
#define STATEIDLETRACKING_H

#include "astate.h"

class StateIdleTracking: public AState
{
public:
    StateIdleTracking(StateMachine *parent, std::shared_ptr<StateChangeManager> stateChangeMgr);

public:
    virtual StateEnum checkNextState();
    virtual std::shared_ptr<IState> goTo(StateEnum state);

protected:
    virtual void procNoStateChange();

private:
    bool needSwitchToActiveTracking();
    void procSwitchToActiveTracking();
    bool needSwitchToNoTracking();
    void procSwitchToNoTracking();
};

#endif // STATEIDLETRACKING_H
