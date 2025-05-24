#pragma once

#include "systemmonitorimpl.h"

class UnixSystemMonitorImpl : public SystemMonitorImpl
{
public:
    explicit UnixSystemMonitorImpl();
    double getCpuUsage() override;
    double getRamUsage() override;
};

