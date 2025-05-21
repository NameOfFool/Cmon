#pragma once

#include <qcustomplot.h>
#include <QObject>
#include <QWidget>
#include <QVector>

class MonitorPlot : public QCustomPlot
{
    Q_OBJECT
public:
    MonitorPlot(QWidget *parent = nullptr);
public slots:
    void updatePlot(double load);
private:
    QVector<double> m_XAxis, m_YAxis;
    int m_seconds = 0;
    static constexpr int DATA_SIZE = 25;
};

