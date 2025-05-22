#include "ramsystemmonitor.h"

#include "unixsystemmonitorimpl.h"

RamSystemMonitor::RamSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double RamSystemMonitor::fetchValue()
{
    return impl->getRamUsage();
}
QScopedPointer<RamSystemMonitor> RamSystemMonitor::createMonitor(QObject *parent)
{
    return QScopedPointer<RamSystemMonitor>(new RamSystemMonitor(parent, new UnixSystemMonitorImpl()));
}
