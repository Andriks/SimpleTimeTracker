#ifndef LINUXSTATEMANAGER_H
#define LINUXSTATEMANAGER_H

#include"iosstatemanager.h"

class LinuxStateManager : public IOSStateManager
{
public:
    unsigned int getIdleTimeMs() override;
    QString getLastAppPid() override;
    QString getLastAppName() override;
    QString getLastAppTitle() override;

private:
    QString exec_cmd(char* cmd);
};

#endif // LINUXSTATEMANAGER_H
