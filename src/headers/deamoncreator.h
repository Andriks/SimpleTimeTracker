
#pragma once

#include "iserver.h"
#include "eventdriverserver.h"
#include "stt_algorithm.h"

#include <string>
#include <memory>
#include <unistd.h>

class DeamonCreator : public IServer
{
private:
    /// Singleton implementation
    DeamonCreator();
    DeamonCreator(DeamonCreator const&) = delete;             // Copy construct
    DeamonCreator(DeamonCreator&&) = delete;                  // Move construct
    DeamonCreator& operator=(DeamonCreator const&) = delete;  // Copy assign
    DeamonCreator& operator=(DeamonCreator &&) = delete;      // Move assign
public:
    static DeamonCreator& Get();

    void start() override;
    void stop() override;
    bool isRunning() override;

private:
    void registerSignals();
    static void handleSignal(const int signum);

    std::string getDeamonPid();
    bool procExists(pid_t pid);

private:
    std::unique_ptr<IServer> mDriver = algo::make_unique<EventDriverServer>();
    static std::string mLockfileName;
};
