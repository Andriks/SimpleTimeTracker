#include <iostream>
#include <fstream>
#include <unistd.h>
#include <signal.h>

#include "AppChangeEventDriver.h"


int main(int argc, char **argv) {
    std::string lockfileName("./bin/lockfile");

    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "start") {
            aced::AppChangeEventDriver driver;
            std::ofstream lockfile;
            pid_t pid;

            pid = fork();
            switch (pid) {
            case -1:
                std::cerr << "can't make fork" << std::endl;
                exit(1);
            case 0:
                std::cout << "===> STT SERVER: server process started!" << std::endl
                          << "===> STT SERVER: server process PID " << getpid() << " <===" << std::endl;
                
                lockfile.open (lockfileName);
                lockfile << getpid() << std::endl;
                lockfile.close();

                driver.start();
            default:
                // will just end parent process
                exit(0);
            }
        } else if (cmd == "stop") {
            std::string pid;
            std::ifstream lockfile(lockfileName);
            if (lockfile.is_open()) {
                getline (lockfile, pid);
                lockfile.close();

                kill(atoi(pid.c_str()), SIGQUIT);
                if ( remove(lockfileName.c_str()) != 0 ) {
                    std::cerr <<  "Error deleting file" << std::endl;
                }

                std::cout << "===> STT SERVER: server process stoped" << std::endl;
            } else {
                std::cout << "===> STT SERVER: server process not started" << std::endl;
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
