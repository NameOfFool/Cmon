#pragma once

#include "systemmonitor.h"
#include <memory>

class RamSystemMonitor : public SystemMonitor
{
public:
    explicit RamSystemMonitor(SystemMonitorImpl *_impl = nullptr);
    double fetchValue() override;
    static std::unique_ptr<RamSystemMonitor> createMonitor();
};

