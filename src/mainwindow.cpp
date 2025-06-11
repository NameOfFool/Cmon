#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ramsystemmonitor.h"
#include "cpusystemmonitor.h"
#include <math.h>
#include <qcustomplot.h>
#include <settingsdialog.h>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, Qt::white);
    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal);
    connect(ui->menuSettings->actions().first(), &QAction::triggered, this, &MainWindow::openSettings);

    cpuMonitorPlot = new MonitorPlot(ui->cpuPlot, CpuSystemMonitor::createMonitor(), tr("CPU_usage"));
    ramMonitorPlot = new MonitorPlot(ui->ramPlot, RamSystemMonitor::createMonitor(), tr("RAM_usage"));
    cpuMonitorPlot->setGeometry(ui->cpuPlot->rect());
    ramMonitorPlot->setGeometry(ui->ramPlot->rect());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSettings()
{
    SettingsDialog dialog(this);
    dialog.exec();
}
