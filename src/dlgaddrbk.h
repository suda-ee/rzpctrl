#ifndef DLGADDRBK_H
#define DLGADDRBK_H

#include <QtGui/QDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QDataWidgetMapper>
#include "ui_dlgaddrbk.h"
#include "addrmodel.h"
#include "config.h"

QT_BEGIN_NAMESPACE

class dlgaddrbk : public QDialog, public Ui::dlgaddrbk
{
    Q_OBJECT
public:
    dlgaddrbk(QWidget *parent = 0);
    ~dlgaddrbk();
    addrmodel *hostsmodel;
    QDomDocument addrdocument;
    QFile *theaddrfile;
    QDataWidgetMapper *mapper;
    bool changed;

public slots:
    void textsynclist(QModelIndex mdlindex);
    void newhostentry();
    void rmhostentry();
    void addrchange();
};

QT_END_NAMESPACE

#endif // DLGADDRBK_H
