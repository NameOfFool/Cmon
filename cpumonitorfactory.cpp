#include "cpumonitor_linux.h"
#include "cpumonitorfactory.h"
std::unique_ptr<CpuMonitor> CpuMonitorFactory::createCpuMonitor(QObject *parent){
    return std::unique_ptr<CpuMonitor>(new LinuxCpuMonitor(parent));
}
