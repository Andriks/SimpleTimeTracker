
#pragma once

class IServer
{
public:
    virtual ~IServer() {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;

    virtual void restart() {
        if (isRunning()) {
            stop();
        }
        start();
    }
};