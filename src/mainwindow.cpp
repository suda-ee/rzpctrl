#include <QtGui/QMessageBox>
#include "mainwindow.h"
#include "optionsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), statusmsg(tr("¾ÍÐ÷£¡"), this)
{
    setupUi(this);
    delete tab;
    statusbar->addWidget(&statusmsg, 0);
    connect(tabwindow, SIGNAL(tabCloseRequested(int)), this, SLOT(closepage(int)));
    connect(CloseTab, SIGNAL(triggered()), this, SLOT(closecurrentpage()));
}

void MainWindow::closepage(int index)
{
    delete tabwindow->widget(index);
}

void MainWindow::closecurrentpage()
{
    delete tabwindow->currentWidget();
}

void MainWindow::showaddrbkdlg()
{
    addrdlg = new dlgaddrbk(this);
    addrdlg->show();
    connect(addrdlg, SIGNAL(accepted()), this, SLOT(addrbkaccept()));
    connect(addrdlg, SIGNAL(rejected()), this, SLOT(addrbkreject()));
}

void MainWindow::addrbkaccept()
{
    int currentrow = addrdlg->addrlist->currentIndex().row();
    if (currentrow > -1)
    {
        QModelIndex idx = addrdlg->hostsmodel->index(currentrow, 0);
        QString alias = addrdlg->hostsmodel->data(idx).toString();
        idx = addrdlg->hostsmodel->index(currentrow, 1);
        QString hostname = addrdlg->hostsmodel->data(idx).toString();
        idx = addrdlg->hostsmodel->index(currentrow, 2);
        quint16 port = addrdlg->hostsmodel->data(idx).toUInt();
        addtabhost(alias, hostname, port);
    }
    delete addrdlg;
}

void MainWindow::addrbkreject()
{
    delete addrdlg;
}

void MainWindow::showquickconndlg()
{
    qkdialog = new quickconn(this);
    qkdialog->show();
    connect(qkdialog, SIGNAL(accepted()), this, SLOT(quickconnaccept()));
    connect(qkdialog, SIGNAL(rejected()), this, SLOT(quickconnreject()));
}

void MainWindow::quickconnaccept()
{
    QString hostname = (qkdialog->lnaddr)->text();
    quint16 port = (qkdialog->sport)->value();
    delete qkdialog;
    addtabhost(hostname, hostname, port);
}

void MainWindow::quickconnreject()
{
    delete qkdialog;
}

void MainWindow::addtabhost(QString &aliasname, QString &hostName, quint16 port)
{
    tabhost *thetab = new tabhost(tabwindow);
    tabwindow->addTab(thetab, thetab->windowIcon(), aliasname);
    tabwindow->setCurrentWidget(thetab);
    connect(thetab, SIGNAL(statusMsg(const QString &)), this, SLOT(setStatusMsg(const QString &)));
    thetab->setAndConn(hostName, port);
}

void MainWindow::tabReconn()
{
    int idx = tabwindow->currentIndex();
    if (idx > -1)
    {
        ((tabhost*)tabwindow->widget(idx))->reconnectskt();
    }
}

void MainWindow::tabDisconn()
{
    int idx = tabwindow->currentIndex();
    if (idx > -1)
    {
        ((tabhost*)tabwindow->widget(idx))->disconnectskt();
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::setStatusMsg(const QString &msg)
{
    statusmsg.setText(msg);
}

void MainWindow::aboutme()
{
    QMessageBox::about(this, tr("¹ØÓÚ"), tr("This software is protected by law and international treaties.\n (C) Soochow 2009."));
}

void MainWindow::showOptionsDialog()
{
    OptionsDialog *optionsdialog;
    optionsdialog = new OptionsDialog(this);
    optionsdialog->exec();
}

