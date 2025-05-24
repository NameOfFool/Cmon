#include "linux/unixsystemmonitorimpl.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <qtypes.h>
#include <fstream>


UnixSystemMonitorImpl::UnixSystemMonitorImpl():SystemMonitorImpl() {}

double UnixSystemMonitorImpl::getCpuUsage()
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
double UnixSystemMonitorImpl::getRamUsage()
{
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open()) {
        return -1.0;  // Ошибка
    }

    std::unordered_map<std::string, double> memData;
    std::string line;

    for (int i = 0; i < 20 && std::getline(meminfo, line); ++i) {
        char key[32];
        double value;
        if (sscanf(line.c_str(), "%31[^:]: %lf kB", key, &value) == 2) {
            memData[key] = value;
        }
    }

    if (memData.count("MemTotal") == 0 || memData.count("MemAvailable") == 0) {
        return -1.0;  // Нет нужных данных
    }

    double total = memData["MemTotal"];
    double available = memData["MemAvailable"];
    double usedPercent = 100.0 * (total - available) / total;

    return usedPercent;
}
