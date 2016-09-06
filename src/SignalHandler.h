
#include "ISignalHandler.h"
#include "CommonTypes.h"

class SignalHandler: public ISignalHandler
{
public:
    ~SignalHandler() override;
    void sendChangeAppEvent(AppInfo newApp) override;

// singleton implementation
public:
    static ISignalHandler& Instance();
private:
    SignalHandler();
    // delete copy and move constructors and assign operators
    SignalHandler(SignalHandler const&) = delete;             // Copy construct
    SignalHandler(SignalHandler&&) = delete;                  // Move construct
    SignalHandler& operator=(SignalHandler const&) = delete;  // Copy assign
    SignalHandler& operator=(SignalHandler &&) = delete;      // Move assign
};
