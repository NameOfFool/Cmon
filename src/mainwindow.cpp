#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ramsystemmonitor.h"
#include "cpusystemmonitor.h"
#include <math.h>
#include <qcustomplot.h>
#include <settingsdialog.h>
#include <QDialog>
#include <QSettings>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings;
    QLocale locale(settings.value("Language", "en_US").toString());
    const QString baseName = "Cmon_" + locale.name()+".qm";
    if (qtTranslator.load(baseName)) {
        qApp->installTranslator(&qtTranslator);
    }

    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, Qt::white);
    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal);
    connect(ui->actionLanguage, &QAction::triggered, this, &MainWindow::openSettings);

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
    if(dialog.exec()==QDialog::Accepted)
    {
        QSettings settings;
        QLocale locale(settings.value("Language", "en_US").toString());
        const QString baseName = "Cmon_" + locale.name()+".qm";
        if (qtTranslator.load(baseName))
        {
            qApp->installTranslator(&qtTranslator);
        }
    }
}
void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        cpuMonitorPlot->updateTranlation(tr("CPU_usage"));
        ramMonitorPlot->updateTranlation(tr("RAM_usage"));
    }

}
