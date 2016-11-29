
#include "Isignalhandler.h"
#include "commontypes.h"

class SignalHandler: public ISignalHandler
{
private:
    /// Singleton implementation
    SignalHandler();
    SignalHandler(SignalHandler const&) = delete;             // Copy construct
    SignalHandler(SignalHandler&&) = delete;                  // Move construct
    SignalHandler& operator=(SignalHandler const&) = delete;  // Copy assign
    SignalHandler& operator=(SignalHandler &&) = delete;      // Move assign
public:
    static ISignalHandler& Get();

    void sendChangeAppEvent(AppInfo newApp) override;

};
