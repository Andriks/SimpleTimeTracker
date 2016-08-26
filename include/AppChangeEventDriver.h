
#pragma once

#include <string>
#include <chrono>

namespace aced {

typedef std::chrono::system_clock::time_point time_point;

struct AppInfo
{
    std::string pid;
    std::string name;
    std::string title;
    time_point timeStarted;
};

class AppChangeEventDriver
{
public:
    AppChangeEventDriver();
    ~AppChangeEventDriver();
    
    void start();

protected:
    void sendChangeEvent(AppInfo newApp);
    std::string exec_cmd(char* cmd);

private:
    time_point mLastPoint;

};


} // aced
