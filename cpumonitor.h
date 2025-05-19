#pragma once

#include <QObject>
#include <QTimer>


class CpuMonitor: public QObject{
    Q_OBJECT

public:
    explicit CpuMonitor(QObject *parent = nullptr);
    ~CpuMonitor(){}

    double cpuLoad() const {return m_cpuLoad;}

signals:
    void cpuLoadUpdate(double load);

public slots:
    void startMonitoring(int intervalMs = 1000);
    void stopMonitoring();
private slots:
    void updateCpuLoad();
protected:
    virtual double calculateCpuLoad() = 0;
    QTimer m_timer;
    double m_cpuLoad = 0.0;
};
