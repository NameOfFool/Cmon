#pragma once

#include <QObject>
#include "systemmonitor.h"
#include <QScopedPointer>

class CpuSystemMonitor : public SystemMonitor
{
public:
    explicit CpuSystemMonitor(QObject *parent = nullptr, SystemMonitorImpl *_impl = nullptr);
    double fetchValue() override;
    static std::unique_ptr<CpuSystemMonitor> createMonitor(QObject *parent = nullptr);
};


