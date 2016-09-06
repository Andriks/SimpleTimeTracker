
#include "DeamonCreator.h"

#include <iostream>
#include <fstream>
#include <signal.h>

std::string DeamonCreator::mLockfileName = "./bin/srvlockfile";

DeamonCreator::DeamonCreator() {}

DeamonCreator& DeamonCreator::Get() {
    static DeamonCreator onlyOne;
    return onlyOne;
}

void DeamonCreator::start() {
    if (isRunning()) {
        std::string pidStr = getDeamonPid();
        std::cout << "===> STT SERVER: server process exists!!!" << std::endl
                  << "===> STT SERVER: server PID " << pidStr <<std::endl;

        exit(0);
    }

    // only one process can reach here, so it is safe
    registerSignals();
    
    std::ofstream lockfile;
    pid_t pid;

    pid = fork();
    switch (pid) {
    case -1:
        std::cerr << "===> STT SERVER: [err] can't make fork" << std::endl;
        exit(1);
    case 0:
        std::cout << "===> STT SERVER: server process started!" << std::endl
                  << "===> STT SERVER: server process PID " << getpid() << " <===" << std::endl;

        lockfile.open(mLockfileName);
        lockfile << getpid() << std::endl;
        lockfile.close();

        mDriver->start();
    default:
        // will just end parent process
        exit(0);
    }
}

void DeamonCreator::stop() {
    if (isRunning()) {
        pid_t pid = atoi(getDeamonPid().c_str());
        if (pid != getpid()) {
            // send SIGQUIT to real deamon process
            kill(pid, SIGQUIT);
            return;
        } else {
            if ( remove(mLockfileName.c_str()) != 0 ) {
                std::cerr <<  "===> STT SERVER: [err] can't delete lockfile" << std::endl;
                return;
            }

            std::cout << "===> STT SERVER: server process stoped" << std::endl;
            mDriver->stop();
            exit(0);
        }
    } else {
        std::cerr << "===> STT SERVER: [err] server process not started" << std::endl;
    }
}

bool DeamonCreator::isRunning() {
    std::string pidStr = getDeamonPid();
    pid_t pid = atoi(pidStr.c_str());
    return procExists(pid);
}

void DeamonCreator::registerSignals() {
    signal(SIGQUIT, &DeamonCreator::handleSignal);
    signal(SIGUSR1, &DeamonCreator::handleSignal);
}

void DeamonCreator::handleSignal(const int signum){
    switch (signum) {
    case SIGQUIT:
        DeamonCreator::Get().stop();
        break;
    case SIGUSR1:
        std::cout << "DeamonCreator::handleSignal --> SIGUSR1" <<std::endl;
        //TODO: do some specific work
        break;
    default:
        break;
    }
}

std::string DeamonCreator::getDeamonPid() {
    std::string result;

    std::ifstream lockfile(mLockfileName);
    if (lockfile.is_open()) {
        getline(lockfile, result);
        lockfile.close();
    }

    return result;
}

bool DeamonCreator::procExists(pid_t pid) {
    bool result = false;
    if (pid > 0) {
        result = (kill(pid, 0) == 0);
    }

    return result;
}
