#pragma once
#include "cpumonitor.h"
#include <QFile>
#include <QTextStream>

class LinuxCpuMonitor : public CpuMonitor{
    Q_OBJECT
public:
    double calculateCpuLoad() override;
    explicit LinuxCpuMonitor(QObject *parent):CpuMonitor(parent){}
};
