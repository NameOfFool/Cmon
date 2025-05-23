#include "cpusystemmonitor.h"

#include "unixsystemmonitorimpl.h"

CpuSystemMonitor::CpuSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double CpuSystemMonitor::fetchValue()
{
    return impl->getCpuUsage();
}
std::unique_ptr<CpuSystemMonitor> CpuSystemMonitor::createMonitor(QObject *parent)
{
    return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(parent, new UnixSystemMonitorImpl()));
}
