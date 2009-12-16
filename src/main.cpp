#include <QtGui/QApplication>
//#include <QtCore>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTranslator qtTranslator;
    //qtTranslator.load("qt_" + QLocale::system().name(),
    //        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    //a.installTranslator(&qtTranslator);

    //QTranslator myappTranslator;
    //myappTranslator.load("rzpctrl_" + QLocale::system().name());
    //a.installTranslator(&myappTranslator);
    MainWindow w;
    w.show();
    w.setWindowState(Qt::WindowMaximized);
    return a.exec();
}
