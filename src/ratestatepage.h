#ifndef RATESTATEPAGE_H
#define RATESTATEPAGE_H

#include <QtGui/QWidget>
#include "ui_ratestatepage.h"

QT_BEGIN_NAMESPACE

class ratestatepage : public QWidget, public Ui::ratestatepage
{
    Q_OBJECT
public:
    ratestatepage(QWidget *parent = 0);
    ~ratestatepage();
};

QT_END_NAMESPACE

#endif // RATESTATEPAGE_H
