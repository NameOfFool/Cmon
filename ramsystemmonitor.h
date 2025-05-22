#pragma once
#include "systemmonitor.h"

class RamSystemMonitor : public SystemMonitor
{
public:
    explicit RamSystemMonitor(QObject *parent = nullptr, SystemMonitorImpl *_impl = nullptr);
    double fetchValue() override;
    static QScopedPointer<RamSystemMonitor> createMonitor(QObject *parent);
};

