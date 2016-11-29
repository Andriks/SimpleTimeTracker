
#include "deamoncreator.h"
#include "reporter.h"

#include <iostream>
#include <vector>
#include <string>

#include <QCoreApplication>

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);

    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "start") {
            DeamonCreator::Get().start();
        } else if (cmd == "stop") {
            DeamonCreator::Get().stop();
        } else if (cmd == "report") {
            std::string request;
            for (int i = 2; i < argc; ++i) {
                request += argv[i];
                if (argc - i > 1) {
                    request += " ";
                }
            }

            Reporter reporter;
            reporter.doReport(request);
        } else {
            std::cerr << "[err]: unknown command" << std::endl;
        }
    } else {
        std::cerr << "[err]: no arguments" << std::endl;
    }

    return 0;
}
