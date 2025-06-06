#include "monitorplot.h"
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QString>

MonitorPlot::MonitorPlot(QWidget *parent, std::unique_ptr<SystemMonitor> systemMonitor, QString title):
    QCustomPlot(parent),
    m_systemMonitor(std::move(systemMonitor))
{
    addGraph();

    hoverLabel = std::make_unique<QCPItemText>(static_cast<QCustomPlot*>(this));
    hoverLabel->setVisible(false);
    hoverLabel->setBrush(QBrush(Qt::white));

    xAxis->setVisible(false);
    xAxis->setRange(0, DATA_SIZE);

    setInteractions(QCP::iSelectPlottables);

    connect(&m_timer, &QTimer::timeout, this, &MonitorPlot::updatePlot);
    connect(this, &MonitorPlot::mouseMove, [=](QMouseEvent *event)
        {
        double x = this->xAxis->pixelToCoord(event->pos().x());
        auto it = this->graph(0)->data()->findBegin(x);

        if(it != this->graph(0)->data()->constEnd() && qAbs(it->key - x) < 0.5)
        {
            hoverLabel->position->setCoords(it->key, it->value + 14);
            hoverLabel->setText(QString("Usage: %1").arg(qRound(it->value)));
            hoverLabel->setVisible(true);
        }
        else
        {
            hoverLabel->setVisible(false);
        }
        this->replot();
    });

    yAxis->setRange(0, 100);
    yAxis->setLabel(tr("Usage %"));

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

    m_timer.start(1000);
}

void MonitorPlot::updatePlot()
{
    double load = m_systemMonitor->fetchValue();

    QCPItemTracer *tracer = new QCPItemTracer(static_cast<QCustomPlot*>(this));
    tracer->setGraph(this->graph(0));
    tracer->setGraphKey(m_seconds);
    tracer->setInterpolating(true);
    tracer->setStyle(QCPItemTracer::tsCircle);
    tracer->setPen(QPen(Qt::red, 2));
    tracer->setSize(2);

    graph(0)->addData(m_seconds,load);
    m_seconds++;

    if(m_seconds > DATA_SIZE)
        xAxis->setRange(m_seconds - DATA_SIZE, m_seconds);

    replot();
}
