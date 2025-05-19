#pragma once
#include <memory>
#include "systemmonitor.h"

class SystemMonitorFactory
{

public:
    static std::unique_ptr<SystemMonitor> createMonitor(QObject *parent);
};
