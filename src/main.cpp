#include <iostream>

#include "AppChangeEventDriver.h"


int main(int argc, char **argv) {
    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "run") {
            aced::AppChangeEventDriver driver;
            driver.start();
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
