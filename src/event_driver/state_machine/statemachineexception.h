#ifndef STATEMACHINEEXCEPTION_H
#define STATEMACHINEEXCEPTION_H

#include <exception>
#include <string>

namespace driver {

class StateMachineException: public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Base StateMachine exception";
    }
};


class UnknownStateException: public StateMachineException
{
public:
    virtual const char* what() const throw()
    {
        return "UnknownState exception";
    }
};

} // driver

#endif // STATEMACHINEEXCEPTION_H
