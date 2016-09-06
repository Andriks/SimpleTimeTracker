
#pragma once

#include "IServer.h"
#include "AppChangeEventDriver.h"

#include <string>
#include <unistd.h>

class DeamonCreator : public IServer
{
private:
    // Singleton implementation
    DeamonCreator();
    DeamonCreator(DeamonCreator const&) = delete;             // Copy construct
    DeamonCreator(DeamonCreator&&) = delete;                  // Move construct
    DeamonCreator& operator=(DeamonCreator const&) = delete;  // Copy assign
    DeamonCreator& operator=(DeamonCreator &&) = delete;      // Move assign
public:
    static DeamonCreator& Get();
    ~DeamonCreator();

    void start() override;
    void stop() override;
    bool isRunning() override;

private:
    void registerSignals();
    static void handleSignal(const int signum);

    std::string getDeamonPid();
    bool procExists(pid_t pid);

private:
    aced::AppChangeEventDriver mDriver;
    static std::string mLockfileName;
};
