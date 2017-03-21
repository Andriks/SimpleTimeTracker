#include "linuxstatemanager.h"

#include <X11/Xlib.h>

namespace driver {

unsigned int LinuxStateManager::getIdleTimeMs()
{
    return exec_cmd("xprintidle").toUInt();
}

QString LinuxStateManager::getLastAppPid()
{
    return exec_cmd("xdotool getactivewindow getwindowpid");
}

QString LinuxStateManager::getLastAppName()
{
    QString pid = getLastAppPid();
    QString name_request = "ps -p " + pid + " -o comm=";
    return exec_cmd(name_request.toStdString().c_str());
}

QString LinuxStateManager::getLastAppTitle()
{
    return exec_cmd("xdotool getwindowfocus getwindowname");
}

QString LinuxStateManager::exec_cmd(char *cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "ERROR\n";
    }

    char buffer[128];
    QString result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }

    pclose(pipe);
    // remove last symbol '\n' before return
    return result.remove(result.size()-1, 1);
}

} // driver
