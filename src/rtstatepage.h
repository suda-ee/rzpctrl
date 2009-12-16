#ifndef RTSTATEPAGE_H
#define RTSTATEPAGE_H

#include <QtGui/QWidget>
#include "ui_rtstatepage.h"

QT_BEGIN_NAMESPACE

class rtstatepage : public QWidget, public Ui::rtstatepage
{
    Q_OBJECT
public:
    rtstatepage(QWidget *parent = 0);
    ~rtstatepage();
};

QT_END_NAMESPACE

#endif // RTSTATEPAGE_H
