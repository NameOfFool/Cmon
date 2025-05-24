#include "cpusystemmonitor.h"

#include "unixsystemmonitorimpl.h"
#include "windowssystemmonitorimpl.h"

CpuSystemMonitor::CpuSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double CpuSystemMonitor::fetchValue()
{
    return impl->getCpuUsage();
}
std::unique_ptr<CpuSystemMonitor> CpuSystemMonitor::createMonitor(QObject *parent)
{
    if(WIN32)
        return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(parent, new WindowsSystemMonitorImpl()));
    else
        return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(parent, new UnixSystemMonitorImpl()));
}
