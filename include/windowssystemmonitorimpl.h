#pragma once

#include "systemmonitorimpl.h"

class WindowsSystemMonitorImpl:public SystemMonitorImpl
{
public:
    explicit WindowsSystemMonitorImpl();
    double getCpuUsage() override;
    double getRamUsage() override;
};