#include <iostream>

#include "DeamonCreator.h"


void makeReport(std::string query);

int main(int argc, char **argv) {

    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "start") {
            DeamonCreator::Get().start();
        } else if (cmd == "stop") {
            DeamonCreator::Get().stop();
        } else if (cmd == "report") {
            makeReport("query");
        } else {
            std::cerr << "[err]: unknown command" << std::endl;
        }
    } else {
        std::cerr << "[err]: no arguments" << std::endl;
    }

    return 0;
}


void makeReport(std::string query) {
    std::cout << "some report here" << std::endl;
}
