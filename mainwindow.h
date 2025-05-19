#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cpumonitor.h"

#include <QLabel>
#include <QMainWindow>

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
    void updateCpuLoad(double load);

private:
    Ui::MainWindow *ui;
    QLabel *cpuLabel;
    std::unique_ptr<CpuMonitor> cpuMonitor;
};
#endif // MAINWINDOW_H
