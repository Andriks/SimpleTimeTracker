#include "configmanagerfactory.h"
#include "reporterconfigmanager.h"

#include <QDebug>


std::shared_ptr<IConfigManager> ConfigManagerFactory::getConfigFor(const ConfigManagerFactory::Components comp)
{
    std::shared_ptr<IConfigManager> result = nullptr;
    switch (comp) {
    case REPORTER:
        result = std::shared_ptr<IConfigManager>(new ReporterConfigManager());
        break;
    default:
        break;
    }

    result->updateConfig();
    return result;
}
