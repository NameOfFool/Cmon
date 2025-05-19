#include "systemmonitorfactory.h"

#include "linuxsystemmonitor.h"

std::unique_ptr<SystemMonitor> SystemMonitorFactory::createMonitor(QObject *parent)
{
    return std::unique_ptr<SystemMonitor>(new LinuxSystemMonitor(parent));
}
