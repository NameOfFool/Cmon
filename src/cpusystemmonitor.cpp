#include "cpusystemmonitor.h"

#include "unixsystemmonitorimpl.h"

CpuSystemMonitor::CpuSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double CpuSystemMonitor::fetchValue()
{
    return impl->getCpuUsage();
}
QScopedPointer<CpuSystemMonitor> CpuSystemMonitor::createMonitor(QObject *parent)
{
    return QScopedPointer<CpuSystemMonitor>(new CpuSystemMonitor(parent, new UnixSystemMonitorImpl()));
}
