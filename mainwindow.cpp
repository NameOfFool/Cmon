#include "cpumonitorfactory.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cpuMonitor = CpuMonitorFactory::createCpuMonitor(this);
    connect(cpuMonitor.get(), &CpuMonitor::cpuLoadUpdate, this, &MainWindow::updateCpuLoad);

    cpuMonitor->startMonitoring();

}

void MainWindow::updateCpuLoad(double load)
{
    // Обновляем текст Label'а из UI-формы
    ui->cpuLoadLabel->setText(QString("CPU: %1%").arg(load, 0, 'f', 1));

    // Можно добавить стилизацию по условию
    QString style;
    if (load > 80) style = "color: red;";
    else if (load > 60) style = "color: orange;";
    else style = "color: green;";

    ui->cpuLoadLabel->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    delete ui;
}

