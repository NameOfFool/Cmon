#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <math.h>
#include <qcustomplot.h>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), systemMonitor(CpuSystemMonitor::createMonitor(this))
{
    ui->setupUi(this);
    monitorPlot = new MonitorPlot(ui->cpuPlot);
    monitorPlot->setGeometry(ui->cpuPlot->rect());

    connect(systemMonitor.get(), &SystemMonitor::valueUpdated, monitorPlot, &MonitorPlot::updatePlot);

    systemMonitor->startMonitoring();

}

MainWindow::~MainWindow()
{
    delete ui;
}

