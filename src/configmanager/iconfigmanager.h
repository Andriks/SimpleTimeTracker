#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QString>
#include <QJsonObject>

class IConfigManager {
public:
    virtual bool isValid() = 0;
    virtual void updateConfig() = 0;
    virtual QJsonValue get(const char* key) = 0;
};

#endif // ICONFIGMANAGER_H
