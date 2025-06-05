#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QString baseName = "Cmon_" + QLocale("en_US").name()+".qm";
    if (translator.load(baseName)) {
        a.installTranslator(&translator);
    }
    MainWindow w;
    w.show();

    return a.exec();
}
