#pragma once

class SystemMonitorImpl
{
public:
    explicit SystemMonitorImpl(){}
    virtual double getCpuUsage() = 0;
    virtual double getRamUsage() = 0;
};
