#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "monitorplot.h"
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openSettings();
private:
    Ui::MainWindow *ui;

    MonitorPlot *cpuMonitorPlot;
    MonitorPlot *ramMonitorPlot;
};
#endif // MAINWINDOW_H
