#include "ramsystemmonitor.h"

#include "unixsystemmonitorimpl.h"

RamSystemMonitor::RamSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double RamSystemMonitor::fetchValue()
{
    return impl->getRamUsage();
}
std::unique_ptr<RamSystemMonitor> RamSystemMonitor::createMonitor(QObject *parent)
{
    return std::unique_ptr<RamSystemMonitor>(new RamSystemMonitor(parent, new UnixSystemMonitorImpl()));
}
