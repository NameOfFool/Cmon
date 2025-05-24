#include "cpusystemmonitor.h"

#include "linux/unixsystemmonitorimpl.h"
#ifdef _WIN32
#include "windows/windowssystemmonitorimpl.h"
#endif

CpuSystemMonitor::CpuSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double CpuSystemMonitor::fetchValue()
{
    return impl->getCpuUsage();
}
std::unique_ptr<CpuSystemMonitor> CpuSystemMonitor::createMonitor(QObject *parent)
{
    #ifdef _WIN32
        return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(parent, new WindowsSystemMonitorImpl()));
    #elif defined(__linux__)
        return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(parent, new UnixSystemMonitorImpl()));
    #endif
}
