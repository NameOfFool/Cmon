#pragma once

#include <qcustomplot.h>
#include <QWidget>
#include "systemmonitor.h"
#include <QString>
#include <QTimer>

class MonitorPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit MonitorPlot(QWidget *parent = nullptr, std::unique_ptr<SystemMonitor> systemMonitor = nullptr, QString title = "");
public slots:
    void updatePlot();
private:
    int m_seconds = 0;
    std::unique_ptr<SystemMonitor> m_systemMonitor;
    static constexpr int DATA_SIZE = 25;
    std::unique_ptr<QCPItemText> hoverLabel;
    QTimer m_timer;
};

