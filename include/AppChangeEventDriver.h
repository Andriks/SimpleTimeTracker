
#pragma once

#include <string>

class AppChangeEventDriver
{
public:
    AppChangeEventDriver();
    ~AppChangeEventDriver();
    
    void start();

private:
    std::string exec_cmd(char* cmd);

};