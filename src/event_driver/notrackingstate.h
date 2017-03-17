#ifndef NOTRACKINGSTATE_H
#define NOTRACKINGSTATE_H

#include <memory>

#include "astate.h"

class NoTrackingState: public AState
{
public:
    NoTrackingState(StateMachine *parent, std::shared_ptr<IOSStateManager> osStateMgr);

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
