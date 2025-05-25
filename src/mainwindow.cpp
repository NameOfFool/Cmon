#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ramsystemmonitor.h"
#include <math.h>
#include <qcustomplot.h>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, Qt::white);
    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal);

    cpuMonitorPlot = new MonitorPlot(ui->cpuPlot, CpuSystemMonitor::createMonitor(), tr("Использование CPU"));
    ramMonitorPlot = new MonitorPlot(ui->ramPlot, RamSystemMonitor::createMonitor(), tr("Использование RAM"));
    cpuMonitorPlot->setGeometry(ui->cpuPlot->rect());
    ramMonitorPlot->setGeometry(ui->ramPlot->rect());

}

MainWindow::~MainWindow()
{
    delete ui;
}

