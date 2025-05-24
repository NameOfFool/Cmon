#include "monitorplot.h"
#include <QPen>
#include <QColor>

MonitorPlot::MonitorPlot(QWidget *parent, std::unique_ptr<SystemMonitor> systemMonitor, QString title):
    QCustomPlot(parent),
    m_XAxis(DATA_SIZE),
    m_YAxis(DATA_SIZE), 
    m_systemMonitor(std::move(systemMonitor))
{
    addGraph();

    xAxis->setVisible(false);
    xAxis->setRange(0, DATA_SIZE);
    connect(m_systemMonitor.get(), &SystemMonitor::valueUpdated, this, &MonitorPlot::updatePlot);

    yAxis->setRange(0, 100);
    yAxis->setLabel("Нагрузка %");
    graph(0)->setPen(QPen(Qt::blue, 2));
    graph(0)->setScatterStyle(QCPScatterStyle(
        QCPScatterStyle::ssDot,
        Qt::red,
        Qt::red,
        10
        ));
    yAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));

    plotLayout()->insertRow(0);
    plotLayout()->addElement(0, 0, new QCPTextElement(this, title, QFont("Fira Code", 14)));

    m_systemMonitor->startMonitoring();
}

void MonitorPlot::updatePlot(double load)
{
    m_seconds++;

    m_XAxis.push_back(m_seconds);
    m_YAxis.push_back(load);

    QCPItemTracer *tracer = new QCPItemTracer(static_cast<QCustomPlot*>(this));
    tracer->setGraph(this->graph(0));
    tracer->setGraphKey(m_seconds);
    tracer->setInterpolating(true);
    tracer->setStyle(QCPItemTracer::tsCircle);
    tracer->setPen(QPen(Qt::red, 2));
    tracer->setSize(2);

    graph(0)->setData(m_XAxis, m_YAxis);

    if(m_seconds > DATA_SIZE)
        xAxis->setRange(m_seconds - DATA_SIZE, m_seconds);

    replot();
}
