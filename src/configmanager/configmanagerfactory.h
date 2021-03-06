#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "iconfigmanager.h"

#include <memory>

class ConfigManagerFactory
{
public:
    enum Components {
        REPORTER = 1,
    };

public:
    ConfigManagerFactory();
    static std::shared_ptr<IConfigManager> getConfigFor(const Components comp);

};

#endif // CONFIGMANAGER_H
