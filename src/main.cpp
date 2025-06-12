#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSettings settings;
    QTranslator qtTranslator;
    QLocale locale(settings.value("Language", "en_US").toString());
    const QString baseName = "Cmon_" + locale.name()+".qm";
    if (qtTranslator.load(baseName)) {
        a.installTranslator(&qtTranslator);
    }
    return a.exec();
}
