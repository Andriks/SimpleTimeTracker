#ifndef IOSSTATEMANAGER_H
#define IOSSTATEMANAGER_H

#include <QString>

namespace driver {

class IOSStateManager
{
public:
    virtual unsigned int getIdleTimeMs() = 0;
    virtual QString getLastAppPid() = 0;
    virtual QString getLastAppName() = 0;
    virtual QString getLastAppTitle() = 0;

};

} // driver

#endif // IOSSTATEMANAGER_H
