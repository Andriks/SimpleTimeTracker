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

public:
    bool isValid() override;
    void updateConfig() override;
    QJsonValue get(const char*  key) override;

private:
    QJsonObject parseFile(QString filename);

private:
    bool mIsValid = false;
    QJsonObject mConfig;

};

#endif // REPORTERCONFIGMANAGER_H
