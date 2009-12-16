#ifndef TABHOST_H
#define TABHOST_H

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>
#include "ui_tabhost.h"
#include "ctlitems.h"
#include "ratestatepage.h"
#include "rtstatepage.h"
#include "rtsetpage.h"

QT_BEGIN_NAMESPACE

class tabhost : public QWidget, public Ui::tabclass
{
    Q_OBJECT
public:
    tabhost(QWidget *parent = 0);
    ~tabhost();

public slots:
    void changepage(QTreeWidgetItem *item, int column);
};

QT_END_NAMESPACE

#endif // TABHOST_H
