#pragma once
#include <QObject>
#include <QTimer>

class SystemMonitor : public QObject
{
    Q_OBJECT
public:
    explicit SystemMonitor(QObject *parent = nullptr);
    virtual ~SystemMonitor() = default;
    double currentUsage() const { return m_currentUsage; }
    bool isMonitoring() const { return m_isMonitoring; }
public slots:
    void startMonitoring(int intervalMs = 1000);
    void stopMonitoring();
signals:
    void valueUpdated(double val);
    void monitoringStarted();
    void monitoringStopped();
protected:
    virtual double fetchValue() = 0;
private slots:
    void updateValue();
private:
    QTimer m_timer;
    double m_currentUsage = 0.0;
    bool m_isMonitoring = false;
};
