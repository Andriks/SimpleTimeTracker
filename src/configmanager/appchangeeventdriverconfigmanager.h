#ifndef APPCHANGEEVENTDRIVERCONFIGMANAGER_H
#define APPCHANGEEVENTDRIVERCONFIGMANAGER_H

#include "iconfigmanager.h"


class AppChangeEventDriverConfigManager: public IConfigManager
{
public:
    const static char* CONFIG_FILENAME;
    const static char* REPORT_FROM_KEY;
    const static char* REPORT_TILL_KEY;

public:
    bool isValid() override;
    void updateConfig() override;
    QJsonValue get(const char*  key) override;

private:
    bool mIsValid = false;
    QJsonObject mConfig;
};

#endif // APPCHANGEEVENTDRIVERCONFIGMANAGER_H
