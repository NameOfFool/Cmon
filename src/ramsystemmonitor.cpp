#include "ramsystemmonitor.h"

#include "linux/unixsystemmonitorimpl.h"
#ifdef _WIN32
#include "windows/windowssystemmonitorimpl.h"
#endif

RamSystemMonitor::RamSystemMonitor(QObject *parent, SystemMonitorImpl *_impl)
    : SystemMonitor(parent, _impl)
{}
double RamSystemMonitor::fetchValue()
{
    return impl->getRamUsage();
}
std::unique_ptr<RamSystemMonitor> RamSystemMonitor::createMonitor(QObject *parent)
{
    #ifdef _WIN32
        return std::unique_ptr<RamSystemMonitor>(new RamSystemMonitor(parent, new WindowsSystemMonitorImpl()));
    #elif defined(__linux__)
        return std::unique_ptr<RamSystemMonitor>(new RamSystemMonitor(parent, new UnixSystemMonitorImpl()));
    #endif
}
