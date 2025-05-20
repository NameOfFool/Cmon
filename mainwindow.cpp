#include "mainwindow.h"
#include "systemmonitorfactory.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>

#include <math.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    systemMonitor = SystemMonitorFactory::createMonitor(this);
    connect(systemMonitor.get(), &SystemMonitor::valueUpdated, this, &MainWindow::updateCpuLoad);


    series = new QLineSeries();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing, false);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->gridLayout->setContentsMargins(0,0,0,0);
    ui->gridLayout->addWidget(chartView);
    systemMonitor->startMonitoring();

}
void MainWindow::updateCpuLoad(double load)
{
    ui->cpuLoadLabel->setText(QString("CPU: %1%").arg(load, 0, 'f', 1));

    QString style;
    if (load > 80) style = "color: red;";
    else if (load > 60) style = "color: orange;";
    else style = "color: green;";

    ui->cpuLoadLabel->setStyleSheet(style);
    series->append(counter++, load);
    auto chart = chartView->chart();
    QAbstractAxis* hAxis = chart->axes(Qt::Horizontal).at(0);
    QAbstractAxis* vAxis = chart->axes(Qt::Vertical).at(0);

    hAxis->setRange(std::max(0, counter-10), counter);
    vAxis->setRange(0, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

