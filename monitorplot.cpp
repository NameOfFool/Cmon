#include "monitorplot.h"

MonitorPlot::MonitorPlot(QWidget *parent): QCustomPlot(parent), m_XAxis(DATA_SIZE), m_YAxis(DATA_SIZE)
{
    addGraph();
    xAxis->setVisible(false);
    xAxis->setRange(0, DATA_SIZE);
    yAxis->setRange(0, 100);
}

void MonitorPlot::updatePlot(double load)
{
    m_seconds++;

    m_XAxis.push_back(m_seconds);
    m_YAxis.push_back(load);

    graph(0)->setData(m_XAxis, m_YAxis);

    if(m_seconds > DATA_SIZE)
        xAxis->setRange(m_seconds - DATA_SIZE, m_seconds);

    replot();
}
