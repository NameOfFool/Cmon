#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "systemmonitor.h"
#include "monitorplot.h"
#include <QLabel>
#include <QMainWindow>
#include <memory>

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
    std::unique_ptr<SystemMonitor> systemMonitor;
    MonitorPlot *monitorPlot;
};
#endif // MAINWINDOW_H
