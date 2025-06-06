#include "cpusystemmonitor.h"

#ifdef _WIN32
#include "windows/windowssystemmonitorimpl.h"
#elif defined(__linux__)
#include "linux/unixsystemmonitorimpl.h"
#endif

CpuSystemMonitor::CpuSystemMonitor(SystemMonitorImpl *_impl)
    : SystemMonitor(_impl)
{}
double CpuSystemMonitor::fetchValue()
{
    return impl->getCpuUsage();
}
std::unique_ptr<CpuSystemMonitor> CpuSystemMonitor::createMonitor()
{
    #ifdef _WIN32
        return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(new WindowsSystemMonitorImpl()));
    #elif defined(__linux__)
        return std::unique_ptr<CpuSystemMonitor>(new CpuSystemMonitor(new UnixSystemMonitorImpl()));
    #endif
}
