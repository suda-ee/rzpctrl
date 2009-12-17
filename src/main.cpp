#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    QFont font = a.font();
    font.setPointSize(9);
    a.setFont(font);
    MainWindow w;
    w.show();
    w.setWindowState(Qt::WindowMaximized);
    return a.exec();
}
