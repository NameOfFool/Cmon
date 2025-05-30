#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "cpusystemmonitor.h"
#include "monitorplot.h"
#include "ramsystemmonitor.h"
#include <QLabel>
#include <QMainWindow>
#include <QScopedPointer>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    MonitorPlot *cpuMonitorPlot;
    MonitorPlot *ramMonitorPlot;
};
#endif // MAINWINDOW_H
