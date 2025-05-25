#pragma once
#include "systemmonitorimpl.h"

#include <QScopedPointer>

class SystemMonitor
{
public:
    explicit SystemMonitor(SystemMonitorImpl *_impl =nullptr);
    virtual ~SystemMonitor() = default;

    double currentUsage() const { return m_currentUsage; }
    virtual double fetchValue() = 0;
protected:
    QScopedPointer<SystemMonitorImpl> impl;
private:
    double m_currentUsage = 0.0;
};
