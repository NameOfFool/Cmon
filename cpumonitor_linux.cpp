#include "cpumonitor_linux.h"
#include <QFile>
#include <QTextStream>

double LinuxCpuMonitor::calculateCpuLoad(){
    static qint64 previousIdle = 0, previousTotal = 0;

    QFile file("/proc/stat");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();

    if(!line.startsWith("cpu "))
        return -1;

    QStringList parts = line.split(' ', Qt::SkipEmptyParts);

    if(parts.size() < 8)
        return -1;
    qint64 idle = parts[4].toLong();
    qint64 total = 0;

    for(int i = 0; i < 8; i++){
        total+=parts[i].toLong();
    }

    qint64 deltaIdle = idle - previousIdle;
    qint64 deltaTotal = idle - previousTotal;

    previousIdle = idle;
    previousTotal = total;

    return 100.0 * (deltaTotal - deltaIdle) / deltaTotal;
}
CpuMonitor::CpuMonitor(QObject *parent):QObject(parent){
    connect(&m_timer, &QTimer::timeout, this, &CpuMonitor::updateCpuLoad);
}
void CpuMonitor::updateCpuLoad(){
    m_cpuLoad = calculateCpuLoad();
    emit cpuLoadUpdate(m_cpuLoad);
}
void CpuMonitor::startMonitoring(int intervalMs){
    m_timer.start(intervalMs);
}
void CpuMonitor::stopMonitoring(){
    m_timer.stop();
}
