#pragma once

#include <qcustomplot.h>
#include <QObject>
#include <QWidget>
#include "systemmonitor.h"
#include <QVector>

class MonitorPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit MonitorPlot(QWidget *parent = nullptr, std::unique_ptr<SystemMonitor> systemMonitor = nullptr);
public slots:
    void updatePlot(double load);
private:
    QVector<double> m_XAxis, m_YAxis;
    int m_seconds = 0;
    std::unique_ptr<SystemMonitor> m_systemMonitor;
    static constexpr int DATA_SIZE = 25;
};

