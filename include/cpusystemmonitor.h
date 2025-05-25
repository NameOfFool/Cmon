#pragma once

#include "systemmonitor.h"
#include <memory>

class CpuSystemMonitor : public SystemMonitor
{
public:
    explicit CpuSystemMonitor(SystemMonitorImpl *_impl = nullptr);
    double fetchValue() override;
    static std::unique_ptr<CpuSystemMonitor> createMonitor();
};


