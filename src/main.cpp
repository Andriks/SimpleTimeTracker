#include <iostream>
#include <unistd.h>

#include "AppChangeEventDriver.h"


int main(int argc, char **argv) {
    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "run") {
            aced::AppChangeEventDriver driver;
            pid_t pid;

            pid = fork();
            switch (pid) {
            case -1:
                std::cerr << "can't make fork" << std::endl;
                exit(1);
            case 0:
                std::cout << "===> STT SERVER: deamon started!" << std::endl
                          << "===> STT SERVER: deamon PID " << getpid() << " <===" << std::endl;

                driver.start();
            default:
                // will just end parent process
                exit(0);
            }
        } else if (cmd == "report") {
            std::cout << "some report here" << std::endl;
        } else {
            std::cout << "unknown command" << std::endl;
        }
    } else {
        std::cout << "no arguments" << std::endl;
    }

    return 0;
}
