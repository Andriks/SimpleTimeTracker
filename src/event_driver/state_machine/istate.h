#ifndef ISTATE_H
#define ISTATE_H

#include <iostream>
#include <memory>

enum class StateEnum;

class IState {
public:
    virtual ~IState(){}
    virtual StateEnum checkNextState() = 0;
//    virtual void goTo(StateEnum state) = 0;
    virtual std::shared_ptr<IState> goTo(StateEnum state) = 0;

protected:
    virtual void procNoStateChange() = 0;

};

#endif // ISTATE_H
