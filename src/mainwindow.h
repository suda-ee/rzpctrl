#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include "ui_mainwindow.h"
#include "dlgaddrbk.h"
#include "quickconn.h"

class MainWindow : public QMainWindow, public Ui::MainWindowClass
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addtabhost(QString &aliasname, QString &hostName, quint16 port);
    QLabel statusmsg;
    dlgaddrbk *addrdlg;
    quickconn *qkdialog;

public slots:
    void aboutme();
    void closepage(int index);
    void closecurrentpage();
    void showaddrbkdlg();
    void addrbkaccept();
    void addrbkreject();
    void showquickconndlg();
    void quickconnaccept();
    void quickconnreject();
    void tabReconn();
    void tabDisconn();
    void setStatusMsg(const QString &msg);

};

#endif // MAINWINDOW_H
