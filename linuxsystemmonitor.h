#pragma once

#include <QObject>
#include "systemmonitor.h"

class LinuxSystemMonitor : public SystemMonitor
{
    Q_OBJECT
public:
    explicit LinuxSystemMonitor(QObject *parent = nullptr);
    ~LinuxSystemMonitor();
protected:
    double fetchValue() override;
};


