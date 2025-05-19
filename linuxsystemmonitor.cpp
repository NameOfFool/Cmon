#include "linuxsystemmonitor.h"

#include <QFile>
#include <QTextStream>

LinuxSystemMonitor::LinuxSystemMonitor(QObject *parent)
    : SystemMonitor{parent}
{

}
LinuxSystemMonitor::~LinuxSystemMonitor(){}
double LinuxSystemMonitor::fetchValue()
{
    static qint64 previousIdle = 0, previousTotal = 0;

    QFile file("/proc/stat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();

    if (!line.startsWith("cpu "))
        return -1;

    QStringList parts = line.split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 8)
        return -1;

    qint64 idle = parts[4].toLongLong();
    qint64 total = 0;
    for (int i = 1; i <= 7; ++i)
        total += parts[i].toLongLong();

    qint64 deltaIdle = idle - previousIdle;
    qint64 deltaTotal = total - previousTotal;

    previousIdle = idle;
    previousTotal = total;

    if (deltaTotal == 0)
        return 0;

    return 100.0 * (deltaTotal - deltaIdle) / deltaTotal;
}
