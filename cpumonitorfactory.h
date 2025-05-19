#pragma once

#include "cpumonitor.h"

class CpuMonitorFactory
{
public:
    static std::unique_ptr<CpuMonitor> createCpuMonitor(QObject *parent = nullptr);
};
