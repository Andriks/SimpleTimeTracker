
#pragma once

#include "AppChangeEventDriver.h"

#include <string>
#include <unistd.h>

class DeamonCreator
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

    void start();
    void stop();

private:
    void registerSignals();
    static void handleSignal(const int signum);

    std::string getDeamonPid();
    bool procExists(pid_t pid);

private:
    aced::AppChangeEventDriver mDriver;
    static std::string mLockfileName;
};
