
#include "deamoncreator.h"
#include "reporter.h"

#include <QCoreApplication>
#include <QString>

#include <QDebug>

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);

    if (argc > 1) {
        QString cmd = argv[1];
        if (cmd == "start") {
            DeamonCreator::Get().start();
        } else if (cmd == "stop") {
            DeamonCreator::Get().stop();
        } else if (cmd == "report") {
            QString request;
            for (int i = 2; i < argc; ++i) {
                request += argv[i];
                if (argc - i > 1) {
                    request += " ";
                }
            }

            Reporter reporter;
            reporter.doReport(request);
        } else {
            qDebug() << "[err]: unknown command";
        }
    } else {
        qDebug() << "[err]: no arguments";
    }

    return 0;
}
