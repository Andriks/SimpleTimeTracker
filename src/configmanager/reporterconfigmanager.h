#ifndef REPORTERCONFIGMANAGER_H
#define REPORTERCONFIGMANAGER_H

#include "iconfigmanager.h"

#include <QString>
#include <QJsonObject>
#include <QJsonValue>

class ReporterConfigManager: public IConfigManager
{
public:
    const static char* CONFIG_FILENAME;
    const static char* DEFAULT_REQUEST_KEY;
    const static char* PRODUCTIVITY_KEY;

    enum Productivity {
        UNMARKED = 0,
        UNPRODUCTIVE = 1,
        NEUTRAL = 2,
        PRODUCTIVE = 3
    };

public:
    bool isValid() override;
    void updateConfig() override;
    QJsonValue get(const char*  key) override;

private:
    bool mIsValid = false;
    QJsonObject mConfig;

};

#endif // REPORTERCONFIGMANAGER_H
