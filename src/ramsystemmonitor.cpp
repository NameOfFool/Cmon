#include "ramsystemmonitor.h"

#include "linux/unixsystemmonitorimpl.h"
#ifdef _WIN32
#include "windows/windowssystemmonitorimpl.h"
#endif

RamSystemMonitor::RamSystemMonitor( SystemMonitorImpl *_impl)
    : SystemMonitor(_impl)
{}
double RamSystemMonitor::fetchValue()
{
    return impl->getRamUsage();
}
std::unique_ptr<RamSystemMonitor> RamSystemMonitor::createMonitor()
{
    #ifdef _WIN32
        return std::unique_ptr<RamSystemMonitor>(new RamSystemMonitor(parent, new WindowsSystemMonitorImpl()));
    #elif defined(__linux__)
        return std::unique_ptr<RamSystemMonitor>(new RamSystemMonitor(new UnixSystemMonitorImpl()));
    #endif
}
