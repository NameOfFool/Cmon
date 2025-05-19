#include "systemmonitor.h"

SystemMonitor::SystemMonitor(QObject *parent)
    : QObject{parent}
{
    connect(&m_timer, &QTimer::timeout, this, &SystemMonitor::updateValue);
}
void SystemMonitor::startMonitoring(int intervalMs)
{
    if(!m_isMonitoring)
    {
        m_timer.start(intervalMs);
        m_isMonitoring = true;
        emit monitoringStarted();
        updateValue();
    }
}
void SystemMonitor::stopMonitoring()
{
    m_timer.stop();
    m_isMonitoring = false;
    emit monitoringStopped();
}
void SystemMonitor::updateValue()
{
    m_currentUsage = fetchValue();
    emit valueUpdated(m_currentUsage);
}

