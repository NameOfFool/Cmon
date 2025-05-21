#pragma once

#include <QObject>
#include "systemmonitor.h"
#include <QScopedPointer>

class CpuSystemMonitor : public SystemMonitor
{
public:
    explicit CpuSystemMonitor(QObject *parent = nullptr, SystemMonitorImpl *_impl = nullptr);
    double fetchValue() override;
    static QScopedPointer<CpuSystemMonitor> createMonitor(QObject *parent);
};


