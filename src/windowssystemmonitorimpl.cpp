#include "windowssystemmonitorimpl.h"
#include <memory>
#include <windows.h>

WindowsSystemMonitorImpl::WindowsSystemMonitorImpl():SystemMonitorImpl(){}

double WindowsSystemMonitorImpl::getCpuUsage()
{
    static ULARGE_INTEGER lastIdleTime, lastKernelTime, lastUserTime;
    
    FILETIME idleTime, kernelTime, userTime;
    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime))
        return -1;

    ULARGE_INTEGER currentIdleTime, currentKernelTime, currentUserTime;
    currentIdleTime.LowPart = idleTime.dwLowDateTime;
    currentIdleTime.HighPart = idleTime.dwHighDateTime;
    currentKernelTime.LowPart = kernelTime.dwLowDateTime;
    currentKernelTime.HighPart = kernelTime.dwHighDateTime;
    currentUserTime.LowPart = userTime.dwLowDateTime;
    currentUserTime.HighPart = userTime.dwHighDateTime;

    ULARGE_INTEGER sysIdleDiff, sysKernelDiff, sysUserDiff;
    sysIdleDiff.QuadPart = currentIdleTime.QuadPart - lastIdleTime.QuadPart;
    sysKernelDiff.QuadPart = currentKernelTime.QuadPart - lastKernelTime.QuadPart;
    sysUserDiff.QuadPart = currentUserTime.QuadPart - lastUserTime.QuadPart;

    lastIdleTime = currentIdleTime;
    lastKernelTime = currentKernelTime;
    lastUserTime = currentUserTime;

    ULONGLONG totalSys = sysKernelDiff.QuadPart + sysUserDiff.QuadPart;
    if (totalSys == 0)
        return 0;

    return 100.0 * (totalSys - sysIdleDiff.QuadPart) / totalSys;
}
double WindowsSystemMonitorImpl::getRamUsage()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    
    if (!GlobalMemoryStatusEx(&memInfo)) {
        return -1.0;  
    }

    double usedPercent = 100.0 - (memInfo.ullAvailPhys * 100.0 / memInfo.ullTotalPhys);
    return usedPercent;
}