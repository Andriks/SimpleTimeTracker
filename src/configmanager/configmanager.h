#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QMap>
#include <QString>
#include <QJsonObject>

class ConfigManager
{
public:
    enum Components {
        REPORT = 1,
    };

public:
    ConfigManager();
    QMap<QString, QString> getConfigFor(const Components comp);

private:
    QJsonObject parseFile(QString filename);

    QMap<QString, QString> getConfigForREPORT();

};

#endif // CONFIGMANAGER_H
