#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "monitorplot.h"
#include <QLabel>
#include <QMainWindow>
#include <QScopedPointer>
#include <QTranslator>
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
protected:
    void changeEvent(QEvent * event) override;
private slots:
    void openSettings();
private:
    Ui::MainWindow *ui;

    MonitorPlot *cpuMonitorPlot;
    MonitorPlot *ramMonitorPlot;

    QTranslator qtTranslator;
};
#endif // MAINWINDOW_H
