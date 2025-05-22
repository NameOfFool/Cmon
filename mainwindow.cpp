#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ramsystemmonitor.h"
#include <math.h>
#include <qcustomplot.h>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),
    cpuSystemMonitor(CpuSystemMonitor::createMonitor(this)),
    ramSystemMonitor(RamSystemMonitor::createMonitor(this))
{
    ui->setupUi(this);

    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, Qt::white);
    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal);

    cpuMonitorPlot = QSharedPointer<MonitorPlot>(new MonitorPlot(ui->cpuPlot));
    ramMonitorPlot = QSharedPointer<MonitorPlot>(new MonitorPlot(ui->ramPlot));
    cpuMonitorPlot->setGeometry(ui->cpuPlot->rect());
    ramMonitorPlot->setGeometry(ui->ramPlot->rect());

    connect(cpuSystemMonitor.get(), &SystemMonitor::valueUpdated, cpuMonitorPlot.get(), &MonitorPlot::updatePlot);
    connect(ramSystemMonitor.get(), &SystemMonitor::valueUpdated, ramMonitorPlot.get(), &MonitorPlot::updatePlot);

    cpuSystemMonitor->startMonitoring();
    ramSystemMonitor->startMonitoring();
}

MainWindow::~MainWindow()
{
    delete ui;
}

